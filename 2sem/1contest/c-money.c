

    int *money = (int *) calloc(N, sizeof(int)); 
    long long cur_sum = 0;

    for (int i = 0; i < N; ++i)
    {
        scanf("%d", &money[i]);
        
        if (money[i] > cur_sum + 1)
        {
            printf("%lld", cur_sum + 1);
            return 0;
        }

        cur_sum += money[i]; 
    }

    printf("%lld", cur_sum + 1);
    
    free(money);
    return 0;
}