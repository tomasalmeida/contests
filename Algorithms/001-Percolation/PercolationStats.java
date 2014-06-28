/*
 * @author: tomás dias almeida
 * PercolationStats
 * Problem described in http://coursera.cs.princeton.edu/algs4/assignments/percolation.html
 */

public class PercolationStats {
    
    private double mMean   = 0.0;
    private double mStdDev = 0.0;
    private double mConfLo = 0.0;
    private double mConfHi = 0.0;
        
    
    // perform T independent computational experiments on an N-by-N grid    
    public PercolationStats(int N, int T) {
        
        if (N < 1 || T < 1)
            throw new java.lang.IllegalArgumentException();
        
        Percolation instance = null;
        int percolateWith = 0;
        
        int i = 0;
        int j = 0;
        int size = N*N;
        
        int[] blockedList = new int[size];
        int   blockedMax = size;
        int chosenRnd = 0;
        int chosen = 0;
        
        double[] meanList = new double[T];
                
        for (int it = 0; it < T; it++) {
            
            instance = new Percolation(N);
            percolateWith = 0;
            while (!instance.percolates()) {                
                
                // get a random blocked size
                chosenRnd = StdRandom.uniform(blockedMax);
                
                //based in th
                if (blockedList[chosenRnd] == 0)
                    chosen = chosenRnd;
                else 
                    chosen = blockedList[chosenRnd];
                
                if (blockedList[blockedMax-1] == 0)
                    blockedList[chosenRnd] = blockedMax-1;
                else                    
                    blockedList[chosenRnd] = blockedList[blockedMax-1];
                    
                    
                i = 1 + (int) Math.floor(((double) chosen) / N);
                j = 1 + (chosen % N);
                instance.open(i, j);
                percolateWith++;
                blockedMax--;
            }
            meanList[it] = ((double) percolateWith)/size;
            mMean += meanList[it];
            blockedList = new int[size];
            blockedMax = size;
        }
        mMean   = mMean/T;
        
        for (int it = 0; it < T; it++) {
            double temp = meanList[it] - mMean;
            mStdDev +=  temp*temp;
        }
        mStdDev = Math.sqrt(mStdDev/(T-1));
        mConfLo = (1.96*mStdDev)/Math.sqrt(T);
        mConfHi = mMean + mConfLo;
        mConfLo = mMean - mConfLo;
    }
    
    // sample mean of percolation threshold
    public double mean() { 
        return mMean;
    }
    
    // sample standard deviation of percolation threshold
    public double stddev() {
        return mStdDev;
    }
    
    // returns lower bound of the 95% confidence interval       
    public double confidenceLo() {
        return mConfLo;
    }
    
    // returns upper bound of the 95% confidence interval
    public double confidenceHi() {
        return mConfHi;
    }
    
    // test client, described below
    public static void main(String[] args) {
        int N = Integer.parseInt(args[0]);
        int T = Integer.parseInt(args[1]);
        
        PercolationStats ps = new PercolationStats(N, T);
        
        
        StdOut.println("mean                    = " + ps.mean());
        StdOut.println("stddev                  = " + ps.stddev());
        StdOut.println("95% confidence interval = " + ps.confidenceLo() 
                                                    + " "+ ps.confidenceHi());
    }
}