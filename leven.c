#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int min(int a, int b, int c){
	int small = a;
	if(small>b){
		small = b;
	}
	if(small>c){
		small = c;
	}
	return small;
}

int DL(const char* a, const char* b, int alen, int blen){ //to get first letter *a, sencond one *(a+1)
	int i;

	int** d_array;

	d_array = malloc((alen+1) *sizeof(int *));

	for(i = 0; i < (alen+1); i++){
		d_array[i] = malloc((blen+1)*sizeof(int));
	}

	for(i=0; i<=alen; i++){
		int j;
		for(j=0; j<=blen; j++){
			d_array[i][j] = 0;
		}
	}

	for(i = 0; i <=alen; i++){
		int j;
		for(j = 0; j<=blen; j++){
		    d_array[i][j]=0;
		    if(i==0 && j==0){
		        d_array[i][j]= 0;
		    }
		    else if(i == 0 && j!=0){
				d_array[0][j] = j;
			}
			else if(j == 0 && i!=0){
				d_array[i][0] = i ;
			}
		}
	}
	

	for(i=1; i<=alen; i++){

		char curra = a[i-1];
		
        int j;
		for(j=1; j<=blen; j++){
			char currb = b[j-1];
            int does = 1;
            if(curra==currb){
                does = 0;
            }

			d_array[i][j] = min(d_array[i-1][j] + 1,//deletion 
								d_array[i][j-1] + 1,//insertion 
								d_array[i-1][j-1] + does);//substitution
			if(i>1 && j>1){
    			char pota = b[j-2];
    		    char potb = a[i-2];
    			if((curra == pota) && (potb == currb)){
    				d_array[i][j] = min(d_array[i][j],
    								d_array[i-2][j-2] + does,
    								d_array[i][j]); //transposition
    			}           
			}
			

		}
	}
	/*
	for(i = 0; i <=(alen); i++){
	    int j;
		for(j = 0; j<=(blen); j++){
			//printf("%d | ", d_array[i][j]);
		}
		//printf("\n");
	}*/

	int last = d_array[alen][blen];

	for(i = 0; i < (alen+1); i++){
		free(d_array[i]);
	}	
	free(d_array);

	return last;
};
/*
int main(){

	const char* first = "ho";
	const char* second = "oh";

	int lena;
	lena = strlen (first);
	int lenb;
	lenb = strlen (second);

	int a = DL(first, second, lena, lenb);

	printf("%d\n", a);
	
	return 0;
}
*/
