LL leastFactor[MAXN];
vector<LL> primes;

void sieve()
{
    LL i, j;

    for(i = 1; i < MAXN; i++)
        leastFactor[i] = (i%2 == 0? 2 : i);

    for(i = 3; i*i < MAXN; i += 2)
    {
        if(leastFactor[i] == i)
        {
            for(j = i*i; j < MAXN; j += 2*i)
                leastFactor[j] = i;
        }
    }

    for(i = 2; i < MAXN; i++)
    {
        if(leastFactor[i] == i)
            primes.push_back(i);
    }
}