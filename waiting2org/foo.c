int foo(int x, int y){
		int x_pow3 = x*x*x;
		if(x_pow3 > 0) return x_pow3;
		return x_pow3 + 17 - x*2 - y*y;
	}
