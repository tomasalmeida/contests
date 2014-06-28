/*
 * @author: tomás dias almeida
 * Percolation
 * Verify if a grid N-by-N percolates
 * Problem described in http://coursera.cs.princeton.edu/algs4/assignments/percolation.html
 */

public class Percolation {
    
    private boolean[] mOpen;
    private int    mNValue;
    private int    mTop;
    private int    mBottom;
    private WeightedQuickUnionUF mQU;
    private WeightedQuickUnionUF mQUWithoutBottom;
    
    // create N-by-N grid, with all sites blocked 
    public Percolation(int N) {
        if (N < 1)
            throw new java.lang.IllegalArgumentException();
        
        int size = N*N;
        mQU              = new WeightedQuickUnionUF(size+2);
        mQUWithoutBottom = new WeightedQuickUnionUF(size+1);
        mOpen = new boolean[size];
        mTop = size;
        mBottom = size+1;
        mNValue = N;
    }   
    
    private int convert2Dto1d(int i, int j) {
        return (i - 1) * mNValue + (j - 1);
    }
    
    private void validateIndex(int i, int j) {
        if (i > mNValue || j > mNValue || i < 1 || j < 1) 
            throw new java.lang.IndexOutOfBoundsException(i + " - " + j);        
    }
    
    // open site (row i, column j) if it is not already
    public void open(int i, int j) {
        validateIndex(i, j);
        
        int pos = convert2Dto1d(i, j);
        if (mOpen[pos]) {
            return;
        } else {
            mOpen[pos] = true;
            
            //connect to mTop
            if (pos < mNValue) {
                mQU.union(mTop,              pos);
                mQUWithoutBottom.union(mTop, pos);
            }
            
            //connect to its top
            if (pos >= mNValue && mOpen[pos - mNValue]) {
                mQU.union(pos,              pos - mNValue);
                mQUWithoutBottom.union(pos, pos - mNValue);
            }
            
            //connect to Bottom
            if (pos + mNValue >= mTop) {
                mQU.union(mBottom, pos);
                //the other QU is not connected to avoid the backwash problem
            }
            
            //connect to its bottom
            if (pos + mNValue < mTop && mOpen[pos + mNValue]) {
                mQU.union(pos,              pos + mNValue);
                mQUWithoutBottom.union(pos, pos + mNValue);
            }
            
            //connect to its left
            if (pos % mNValue != 0 && mOpen[pos - 1]) {
                mQU.union(pos,              pos - 1);
                mQUWithoutBottom.union(pos, pos - 1);
            }
            
            //connect to its right
            if ((pos+1) % mNValue != 0 && mOpen[pos + 1]) {
                mQU.union(pos,              pos + 1);                
                mQUWithoutBottom.union(pos, pos + 1);
            }
        }
    }
    
    // is site (row i, column j) open?
    public boolean isOpen(int i, int j) {
        validateIndex(i, j);
        
        return mOpen[convert2Dto1d(i, j)];
    }
    
    // is site (row i, column j) full?
    public boolean isFull(int i, int j) {
        validateIndex(i, j);
        
        // do not use the other QU because can cause the backwash problem
        return mQUWithoutBottom.connected(mTop, convert2Dto1d(i, j));
    }
    
    // does the system percolate?        
    public boolean percolates() {
        return mQU.connected(mTop, mBottom);
    }    
}