`include "config.inc"

module video2ram(
    input clock,
    input nreset,
    
    input [7:0] R,
    input [7:0] G,
    input [7:0] B,
    input [11:0] counterX,
    input [11:0] counterY,
    
    input line_doubler,
    
    output [23:0] wrdata,
    output [14:0] wraddr,
    output wren,
    output wrclock,
    
    output starttrigger,

    input DCVideoConfig dcVideoConfig
);

    reg [9:0] H_CAPTURE_START;
    reg [9:0] H_CAPTURE_END;
    reg [9:0] V_CAPTURE_START;
    reg [9:0] V_CAPTURE_END;

    reg wren_reg;
    reg [23:0] wrdata_reg;
    reg [14:0] wraddr_reg;
    reg [14:0] ram_addrY_reg;
    reg trigger;
    reg [11:0] counterX_prev;

    always @(*) begin
        if (line_doubler) begin
            H_CAPTURE_START = dcVideoConfig.i_horizontal_capture_start;
            H_CAPTURE_END   = dcVideoConfig.i_horizontal_capture_end;
            V_CAPTURE_START = dcVideoConfig.i_vertical_capture_start;
            V_CAPTURE_END   = dcVideoConfig.i_vertical_capture_end;
        end else begin
            H_CAPTURE_START = dcVideoConfig.p_horizontal_capture_start;
            H_CAPTURE_END   = dcVideoConfig.p_horizontal_capture_end;
            V_CAPTURE_START = dcVideoConfig.p_vertical_capture_start;
            V_CAPTURE_END   = dcVideoConfig.p_vertical_capture_end;
        end
    end

    `define GetWriteAddr(x) (ram_addrY_reg + (x - H_CAPTURE_START))
    `define IsFirstBuffer(y)   ((y - V_CAPTURE_START) < dcVideoConfig.buffer_size)
    `define IsTriggerPoint(y) (`IsFirstBuffer(y) && wraddr_reg == (line_doubler ? dcVideoConfig.trigger_address_i : dcVideoConfig.trigger_address_p))

    `define IsVerticalCaptureTime(y) ( \
        line_doubler \
            ? (y < 240 || (y > 262 && y < V_CAPTURE_END)) \
            : (y >= V_CAPTURE_START && y < V_CAPTURE_END) \
    )
    `define IsCaptureTime(x,y) ( \
        `IsVerticalCaptureTime(y) && x >= H_CAPTURE_START && x < H_CAPTURE_END \
    )

    initial begin
        wren_reg <= 0;
        wrdata_reg <= 24'd0;
        wraddr_reg <= 0;
        ram_addrY_reg <= 0;
        trigger <= 0;
    end

    always @ (posedge clock or negedge nreset) begin
        if (~nreset) begin
            wren_reg <= 0;
            wrdata_reg <= 24'd0;
            wraddr_reg <= 0;
            ram_addrY_reg <= 0;
            trigger <= 0;
        end else begin
            counterX_prev <= counterX;

            if (counterX_prev == H_CAPTURE_END && counterX == H_CAPTURE_END) begin // calculate ram_addrY_reg once per line
                if (`IsVerticalCaptureTime(counterY)
                && ram_addrY_reg < dcVideoConfig.ram_numwords - dcVideoConfig.buffer_line_length) begin
                    ram_addrY_reg <= ram_addrY_reg + dcVideoConfig.buffer_line_length;
                end else begin
                    ram_addrY_reg <= 0;
                end
            end

            if (`IsCaptureTime(counterX, counterY)) begin
                wren_reg <= 1;
                wraddr_reg <= `GetWriteAddr(counterX);
                wrdata_reg <= { R, G, B };

                if (`IsTriggerPoint(counterY)) begin
                    trigger <= 1'b1;
                end else begin
                    trigger <= 1'b0;
                end
            end else begin
                wren_reg <= 0;
                trigger <= 1'b0;
            end
        end
    end

    assign wren = wren_reg;
    assign wrclock = clock;
    assign wraddr = wraddr_reg;
    assign wrdata = wrdata_reg;
    assign starttrigger = trigger;
    
endmodule