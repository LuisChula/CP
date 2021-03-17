public class Main {

    public static void main( String args[] ) {

        int nPoints = Integer.parseInt(args[0]);  
        int nThreads = 1;
        if(args.length > 1 && args[1] != "0") {
            nThreads = Integer.parseInt(args[1]);
        }

        int m = nPoints / nThreads;
        MonteCarloPI[] mcps = new MonteCarloPI[nThreads];
        Thread[] ts = new Thread[nThreads];
        for(int i = 0; i < nThreads; i++){
            MonteCarloPI mcp = new MonteCarloPI(m);
            Thread t = new Thread(mcp);
            t.start();
            mcps[i] = mcp;
            ts[i] = t;
        }

        int within = 0;
        for(int i = 0; i < nThreads; i++) {
            try{
                //System.out.println("thread before"+i);
                ts[i].join();
                //System.out.println("thread after"+i);
                within += mcps[i].getWithin();
                //System.out.println(mcps[i].getWithin());
            } catch(Exception e){
                System.out.println(e);
            }
        }

        double pi = 4.0*((double)within/(double)nPoints);
        MonteCarloPI.print(nPoints, within, pi);
    }

}