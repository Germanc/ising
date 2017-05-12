float energia(int *lattice, int n, float T, float B){
    int i;
    float energ =0;
    int S, E, O, N;
    float J = 1.0/T;
    for(i=0;i<n*n;i++){
        E = (i%(n-1) == 0) ? i-n+1 : i+1;
        if(E<0) E = 1;
        S = (i>=n*(n-1)-1) ? i-(n*(n-1)) : i+n;
        energ += -J*lattice[i]*(lattice[E]+lattice[S])-B*lattice[i];
    }
    return energ;;
}
