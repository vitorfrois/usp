void printPowerSet(char* set, int set_size){
    
    // Set_size of power set of a set with set_size
    // n is (2^n-1)
    unsigned int pow_set_size = pow(2, set_size);
    int counter, j;
 
    // Run from counter 000..0 to 111..1
    for (counter = 0; counter < pow_set_size; counter++) {
        for (j = 0; j < set_size; j++) {
            // Check if jth bit in the counter is set
            // If set then print jth element from set
            if (counter & (1 << j))
                cout << set[j];
        }
        cout << endl;
    }
}