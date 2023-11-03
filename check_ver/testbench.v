`timescale 1ms / 1 ms

module testbench();

reg tb_rst, tb_clk;
wire [3:0]value;

always
	#5 tb_clk = ~tb_clk;
initial
begin
	$dumpfile("waves.vcd");
	$dumpvars(0, testbench);

	$display("starting testbench!");
	tb_rst = 1;
	tb_clk = 0;
	#10;
	tb_rst = 0;

	#73;
	tb_rst = 1;
	#11;
	tb_rst = 0;

	#134;
	tb_rst = 1;
	#57;
	tb_rst = 0;
	#200;
	$display("finished ok!");
	$finish;
end

sample my_sample_inst(
	.reset(tb_rst),
	.clk(tb_clk),
	.cnt(value)
);

wire fail;
assign fail = (tb_rst & value!=0);

endmodule






