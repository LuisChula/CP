import java.util.*;

public class MonteCarloPI {

    private static boolean isInTheCircle(double x, double y){
        return (Math.pow(x, 2) + Math.pow(y, 2) < 1) ? true : false;
    }

    private static void print(int nPoints, int within, double pi){
        System.out.println("Total Number of points: " + nPoints);
        System.out.println("Points within circle: " + within);
        System.out.println("Pi estimation: " + pi);
    }

    public static void main(String[] args) {
        int nPoints = Integer.parseInt(args[0]);
        Random r = new Random();
        int within = 0;
        for(int i = 0; i < nPoints; i++){
            double x = r.nextDouble();
            double y = r.nextDouble();
            if(isInTheCircle(x, y))
                within++;
        }
        
        double pi = 4.0*((double)within/(double)nPoints);

        print(nPoints, within, pi);
        
    } 
    
}