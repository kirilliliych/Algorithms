
{
    int N = 0;
    int M = 0;
    scanf("%d %d", &N, &M);

    int *array = (int *) calloc(N, sizeof(int));
    long long *samples_array = (long long *) calloc(M, sizeof(long long));

    for (int i = 0; i < N; ++i)
    {
        scanf("%d", &array[i]);
    }

    for (int i = 0; i < M; ++i)
    {
        scanf("%lld", &samples_array[i]);
    }

    for (int i = 0; i < M; ++i)
    {
        int *left_ptr  = array;
        int *right_ptr = left_ptr + 1;
        long long cur_sum = *left_ptr + *right_ptr;
        int flag = 0;

        while ((left_ptr - array < N) && (right_ptr - array < N))
        {
            if (cur_sum < samples_array[i])
            {
                ++right_ptr;
                cur_sum += *right_ptr;
            }
            else if (cur_sum == samples_array[i])
            {
                printf("%ld %ld\n", left_ptr - array + 1, right_ptr - array + 2);
                flag = 1;
                break;
            }
            else if (cur_sum > samples_array[i])
            {
                cur_sum -= *left_ptr;
                ++left_ptr;
            }
        }

        if (flag != 1)
        {
            printf("Not found\n");
        }
    }

    free(array);
    free(samples_array);

    return 0;
}