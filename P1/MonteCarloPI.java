import java.util.*;

public class MonteCarloPI implements Runnable {

    private int nPoints;
    private int within;

    public MonteCarloPI(int nPoints){
        this.nPoints = nPoints;
        within = -1;
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
        Random r = new Random();
        try {
            within = 0;
            for(int i = 0; i < nPoints; i++){
                double x = r.nextDouble();
                double y = r.nextDouble();
                if(isInTheCircle(x, y))
                    within++;
            }
        } catch(Exception e){
            System.out.println(e);
        }
    } 
    
}