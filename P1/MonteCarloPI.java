import java.util.*;

public class MonteCarloPI {

    private static double randInt(int rangeMin, int rangeMax) {
        Random r = new Random();
        double randomValue = rangeMin + (rangeMax - rangeMin) * r.nextDouble();
        return randomValue;
    }

    private static boolean isInTheCircle(double x, double y){
        System.out.println("("+x+","+y+")");
        return (Math.pow(x, 2) + Math.pow(y, 2) < 1) ? true : false;
    }

    public static void main(String[] args) {
        int nPoints = Integer.parseInt(args[0]);
        int m = 0;
        for(int i = 0; i < nPoints; i++){
            double x = randInt(-1, 1);
            double y = randInt(-1, 1);
            if(isInTheCircle(x, y))
                m++;
        }
        
    } 
    
}