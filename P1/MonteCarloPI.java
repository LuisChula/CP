import java.util.*;

public class MonteCarloPI implements Runnable {

    private int nPoints;
    private volatile int within;

    public MonteCarloPI(int nPoints){
        this.nPoints = nPoints;
        within = -1;
    }

    private static double randInt(int rangeMin, int rangeMax) {
        Random r = new Random();
        double randomValue = rangeMin + (rangeMax - rangeMin) * r.nextDouble();
        return randomValue;
    }

    private static boolean isInTheCircle(double x, double y){
        return (Math.pow(x, 2) + Math.pow(y, 2) < 1) ? true : false;
    }

    public static void print(int nPoints, int within, double pi){
        System.out.println("Total Number of points: " + nPoints);
        System.out.println("Points within circle: " + within);
        System.out.println("Pi estimation: " + pi);
    }

    public int getWithin(){
        return within;
    }

    @Override
    public void run() {
        try {
            within = 0;
            for(int i = 0; i < nPoints; i++){
                double x = randInt(-1, 1);
                double y = randInt(-1, 1);
                if(isInTheCircle(x, y))
                    within++;
            }
            this.within = within;
            /*double pi = 4.0*((double)within/(double)nPoints);
            print(nPoints, within, pi);*/

        } catch(Exception e){
            System.out.println(e);
        }
    } 
    
}