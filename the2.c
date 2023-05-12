#include <stdio.h>
#include <stdlib.h>
char *pos;
int isspace(int c);
int islower(int c);
int f_iff(int x, int y){
    if(x&&(!y)) return 0;
    else return 1;
}
int f_or(int x, int y){
    if((!x)&&(!y)) return 0;
    else return 1;
}
int evaluate(int* table){
    int right,left;
    char opr;
    if(*pos=='('){
        pos++;
        left=evaluate(table);
        opr=*pos++;
        right=evaluate(table);
        pos++;
            switch(opr){
            case('&'):
                return left&&right;
            break;
            case('|'):
                return left||right;
            break;
            case('>'):
                return f_iff(left,right);
            break;
            case('='):
                return left==right;
            break;
            default: 
                printf("error parsing\n");                     
        } 
    }
    else if(*pos=='-'){
        pos++;
        right=evaluate(table);
        return !right;
    }
    else{
        pos++;
        return table[*(pos-1)-97];
    }
    return 0;
}
int main() {
    char *expr;
    char *var;
    char temp;
    int a;
    int len_var;
    int exp_var;
    int len;
    int i;
    int j;
    int n,c;
    int found;
    int** truth;
    expr=malloc(0);
    var=malloc(0);
    len=0;
    len_var=0;
    exp_var=1;
    while((a=getchar())!=EOF){
        found=0;
        if(!(isspace(a))){
            len++;
            expr=(char*)realloc(expr,len*sizeof(char));
            expr[len-1]=a;
        }
        if(islower(a)){
            for(i=0;i<len_var;i++){
               if(var[i]==a){
                   found=1;
               } 
            } 
            if(found==0){   
                len_var++;
                exp_var=exp_var*2;
                var=(char*)realloc(var,len_var*sizeof(char));
                var[len_var-1]=a;
            }
        }
    }
    for (i = 0; i < len_var-1; i++) {
      for (j = i+1; j < len_var; j++) {
         if (var[i] > var[j]) {
            temp = var[i];
            var[i] = var[j];
            var[j] = temp;
         }
      }
   }
    truth=(int**)malloc((exp_var)*sizeof(int*));
    for (i=0;i<(exp_var);i++){
        truth[i]=malloc(27*sizeof(int));
        for(j=0;j<27;j++){
            truth[i][j]=-1;
        }
    }
    for (i=exp_var-1;i>=0;i--){
        for (c = len_var; c > 0; c--){
            n = i >> (c-1);
            if (n & 1){
                truth[i][var[len_var-c]-97]=1;
            }
            else{
                truth[i][var[len_var-c]-97]=0;
            }
        }
    }
    pos=expr;
    for(i=0;i<len_var;i++){
        printf("%c ",var[i]);
    }
    printf("R\n");
    for (i=0;i<exp_var;i++){
        pos=expr;
        truth[exp_var-1-i][26]=evaluate(truth[exp_var-1-i]);
        for(j=0;j<26;j++){
            if((truth[i][j])==1) printf("F ");
            else if(truth[i][j]==0) printf("T ");
        }
        if(truth[exp_var-1-i][26]) printf("T\n");
        else if(!(truth[exp_var-1-i][26])) printf("F\n");
    }
    free(expr);
    free(var);
    for (i=0;i<(exp_var);i++){
        free(truth[i]);
    }
    free(truth);
    return 0;

}

