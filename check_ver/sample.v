module sample(
	input wire reset,
	input wire clk,
	output reg [3:0]cnt
);

always @(posedge clk or posedge reset)
	if(reset)
	cnt<=0;
	else
	cnt<=cnt+1;
endmodule
