#include "semantic.h"
#include "syntax.tab.h"

extern pNode root;

extern int yylineno;
extern int yyparse();
extern void yyrestart(FILE*);

unsigned lexError = FALSE;
unsigned synError = FALSE;

int main(int argc, char** argv) {
            char name[100] = {0};

    FILE* f = NULL;
    if (argc <= 1) {
        FILE* cf = fopen("current.txt","r");
        int curr = 1;
        if(!cf){
            //perror("current");
            //return 1;
        }else{
            fscanf(cf,"%d",&curr);
            fclose(cf);
            cf = fopen("current.txt","w");
            if(cf){
                int nextcur = curr==23?1:curr+1;
                fprintf(cf,"%d",nextcur);
                fclose(cf);
            }else{
                printf("自更新失败！\n");
            }
            
        }
        sprintf(name,"CODE%d.cmm",curr);
        f = fopen(name,"r");
    }else{
        f = fopen(argv[1], "r");
        strcpy(name,argv[1]);
    }
    if (!f) {
        perror(name);
        return 1;
    }
    printf("当前文件：%s\n",name);
    printf("=================\n");
    char c = fgetc(f);
    int lno = 1;
    printf("  1 |");
    while(c!=EOF && c!=NULL){
        printf("%c",c);
        if(c=='\n') printf("%3d |",++lno);
        c = fgetc(f);
    }
    printf("\n=================\n");
    fclose(f);

    f = fopen(name,"r");
    if (!f) {
        perror(name);
        return 1;
    }

    yyrestart(f);
    yyparse();
    if (!lexError && !synError) {
        table = initTable();
        // printTreeInfo(root, 0);
        traverseTree(root);
        deleteTable(table);
    }
    delNode(&root);
    return 0;
}
