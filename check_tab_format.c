
void copy(int *to, int const *from, int count){
	int n = (count + 3) / 4;
	switch(count%4){
		case 0: do { *to++ = *from++;
		case 3:	     *to++ = *from++;
		case 2:      *to++ = *from++;
		case 1:      *to++ = *from++;
		        } while (--n > 0);
	}
}
