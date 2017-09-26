
int main()
{
    int i =-1;
    char *s1, *s2, *s3, *s4, *s5, *s6, *s7, *s8, *s9, *s10,*s11,*s12,*s13,*s14,*s15,*s16,*s17,*s18,*s19,*s20;

    s1 = (char *)my_malloc(sizeof(char) * 21);
    if (s1){
        while (++i < 10)
            s1[i] = 'a';
        s1[i] = '\0';
        i=-1;
    }

    s2 = (char *)my_malloc(sizeof(char) * 500);
    if (s2){
        while (++i < 10)
            s2[i] = 'b';
        s2[i] = '\0';
        i=-1;
    }

    s3 = (char *)my_malloc(sizeof(char) * 200);
    if (s3){
        while (++i < 10)
            s3[i] = 'c';
        s3[i] = '\0';
        i=-1;
    }

    s4 = (char *)my_malloc(sizeof(char) * 10);
    if (s4){
        while (++i < 10)
            s4[i] = 'd';
        s4[i] = '\0';
        i=-1;
    }

    s5 = (char *)my_malloc(sizeof(char) * 11);
    if (s5){
        while (++i < 10)
            s5[i] = 'e';
        s5[i] = '\0';
        i=-1;
    }

    s6 = (char *)my_malloc(sizeof(char) * 400);
    if (s6){
        while (++i < 10)
            s6[i] = 'f';
        s6[i] = '\0';
        i=-1;
    }

    s7 = (char *)my_malloc(sizeof(char) * 400);
    if (s7){
        while (++i < 10)
            s7[i] = 'g';
        s7[i] = '\0';
        i=-1;
    }

    s8 = (char *)my_malloc(sizeof(char) * 1000);
    if (s8){
        while (++i < 10)
            s8[i] = 'h';
        s8[i] = '\0';
        i=-1;
    }
    s9 = (char *)my_malloc(sizeof(char) * 300);
    if (s9){
        while (++i < 10)
            s9[i] = 'i';
        s9[i] = '\0';
        i=-1;
    }

    s10 = (char *)my_malloc(sizeof(char) * 9000);
    if (s10){
        while (++i < 10)
            s10[i] = 'j';
        s10[i] = '\0';
        i=-1;
    }
    
   
    
    show_alloc_mem();
    /*impress();
    printf("\n\n\n\n\n\n\n");*/my_free(s4);my_free(s3);

    show_alloc_mem();
    s11 = (char *)my_malloc(sizeof(char) * 205);
    if (s11){
        while (++i < 100)
            s11[i] = '1';
        s11[i] = '\0';
        i=-1;
    }
 
    printf("\n\n\nnew\n\n\n");
    show_alloc_mem();
    
    /*my_free(s1);

    show_alloc_mem();
    printf("asking::: %lu\n", sizeof(t_block));
    
    s20 = (char *)my_malloc(sizeof(char) * 20);
    printf("asking::: %lu\n", sizeof(char) * 12);
    
    show_alloc_mem();
    if (s20){
        while (++i < 10)
            s20[i] = 'p';
        s20[i] = '\0';
        i=-1;
    }
    my_free(s5);
    printf("\n\n\nnew\n\n\n");
    show_alloc_mem();*/

    my_free(s1);
    show_alloc_mem();
    my_free(s2);
    show_alloc_mem();
    my_free(s3);
    show_alloc_mem();
    my_free(s4);
    show_alloc_mem();
    my_free(s5);
    show_alloc_mem();
    my_free(s6);
    show_alloc_mem();
    my_free(s7);
    show_alloc_mem();
    my_free(s8);
    show_alloc_mem();
    my_free(s9);
    show_alloc_mem();
    my_free(s10);
    show_alloc_mem();
    my_free(s11);
    show_alloc_mem();
    my_free(s20);
    show_alloc_mem();
 i =-1;

    s1 = (char *)my_malloc(sizeof(char) * 21);
    if (s1){
        while (++i < 10)
            s1[i] = 'a';
        s1[i] = '\0';
        i=-1;
    }

    s2 = (char *)my_malloc(sizeof(char) * 500);
    if (s2){
        while (++i < 10)
            s2[i] = 'b';
        s2[i] = '\0';
        i=-1;
    }

    s3 = (char *)my_malloc(sizeof(char) * 200);
    if (s3){
        while (++i < 10)
            s3[i] = 'c';
        s3[i] = '\0';
        i=-1;
    }

    s4 = (char *)my_malloc(sizeof(char) * 10);
    if (s4){
        while (++i < 10)
            s4[i] = 'd';
        s4[i] = '\0';
        i=-1;
    }

    s5 = (char *)my_malloc(sizeof(char) * 11);
    if (s5){
        while (++i < 10)
            s5[i] = 'e';
        s5[i] = '\0';
        i=-1;
    }

    s6 = (char *)my_malloc(sizeof(char) * 400);
    if (s6){
        while (++i < 10)
            s6[i] = 'f';
        s6[i] = '\0';
        i=-1;
    }

    s7 = (char *)my_malloc(sizeof(char) * 400);
    if (s7){
        while (++i < 10)
            s7[i] = 'g';
        s7[i] = '\0';
        i=-1;
    }

    s8 = (char *)my_malloc(sizeof(char) * 1000);
    if (s8){
        while (++i < 10)
            s8[i] = 'h';
        s8[i] = '\0';
        i=-1;
    }
    s9 = (char *)my_malloc(sizeof(char) * 300);
    if (s9){
        while (++i < 10)
            s9[i] = 'i';
        s9[i] = '\0';
        i=-1;
    }

    s10 = (char *)my_malloc(sizeof(char) * 9000);
    if (s10){
        while (++i < 10)
            s10[i] = 'j';
        s10[i] = '\0';
        i=-1;
    }
    
   
    
    show_alloc_mem();
    /*impress();
    printf("\n\n\n\n\n\n\n");*/my_free(s4);my_free(s3);

    show_alloc_mem();
    s11 = (char *)my_malloc(sizeof(char) * 205);
    if (s11){
        while (++i < 100)
            s11[i] = '1';
        s11[i] = '\0';
        i=-1;
    }
 
    printf("\n\n\nnew\n\n\n");
    show_alloc_mem();
    
    /*my_free(s1);

    show_alloc_mem();
    printf("asking::: %lu\n", sizeof(t_block));
    
    s20 = (char *)my_malloc(sizeof(char) * 20);
    printf("asking::: %lu\n", sizeof(char) * 12);
    
    show_alloc_mem();
    if (s20){
        while (++i < 10)
            s20[i] = 'p';
        s20[i] = '\0';
        i=-1;
    }
    my_free(s5);
    printf("\n\n\nnew\n\n\n");
    show_alloc_mem();*/

    return 0;
}
