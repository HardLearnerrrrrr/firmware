public class test {
    public static void main(String[] args) {
        double[] x1 = {1,1,0.3,0.6,1.2,1.8,1.5,3,4,3.1,3.6,3.8,3.5,3.5};
        double[] x2 = {1,2,1.2,0.8,1,1,2,1.4,3,4,3.3,3.8,2.1,2.2,2.8};
        double[] y = {0,0,0,0,0,0,0,0,1,1,1,1,1,1,1};
        optimizerSGD(x1,x2,y,x1.length);
        //optimizerBatch(x1,x2,y,x1.length);
    }
    public static void optimizerSGD(double[] x1,double[] x2 ,double[] y,int m){
        //参数 a b c  初始值随机定义
        double a = 0.1;
        double b = 0.5;
        double c = 0;
 
        int count = 0; //当前循环次数
 
        int loop = 2000; //最大循环次数
        double loss = 0; // 损失值
        double alpha = 1; //学习率
        while (count<loop){
            for(int i =0;i<m;i++){
                double diff = (float)sigmoid(a * x1[i] + b * x2[i] + c) - y[i];
                a -= alpha *diff * x1[i];
                b -= alpha *diff * x2[i];
                c -= alpha *diff;
            }
            count++;
            for(int i =0;i<m;i++){
                //System.out.println(a*x1[i]+b*x2[i]+c);
                loss += -y[i]*Math.log(sigmoid(a * x1[i] + b * x2[i] + c));
            }
            loss = loss / m;
            System.out.println(count+"_"+loss);
        }
 
        for(int i =0;i<x1.length;i++){
            System.out.println("ypre"+i+"_"+sigmoid(a * x1[i] + b * x2[i] + c));
        }
        System.out.println("a_"+a);
        System.out.println("b_"+b);
        System.out.println("c_"+c);
        System.out.println("loss_"+loss);
    }
 
 
    public static void optimizerBatch(double[] x1,double[] x2 ,double[] y,int m){
        //参数 a b c
        double a = 0.1;
        double b = 0.5;
        double c = 0;
 
        int count = 0; //当前循环次数
 
        int loop = 2000; //最大循环次数
        double loss = 0; // 损失值
        double alpha = 1; //学习率
        while (count<loop){
            double diffx1 = 0;
            double diff = 0;
            double diffx2 = 0;
            for (int j = 0; j < m; j++) {
                diff += sigmoid(a * x1[j] + b * x2[j] + c)- y[j];
                diffx1 += (sigmoid(a * x1[j] + b * x2[j] + c) - y[j])*x1[j];
                diffx2 += (sigmoid(a * x1[j] + b * x2[j] + c) - y[j])*x2[j];
            }
            a -= alpha * diffx1  / m;
            b -= alpha * diffx2 / m;
            c -= alpha * diff /m;
 
            count++;
            for(int i =0;i<m;i++){
                //System.out.println(a*x1[i]+b*x2[i]+c);
                loss += -y[i]*Math.log(sigmoid(a * x1[i] + b * x2[i] + c));
            }
            loss = loss / m;
            System.out.println(count+"_"+loss);
        }
        for(int i =0;i<x1.length;i++){
            System.out.println("ypre"+i+"_"+sigmoid(a * x1[i] + b * x2[i] + c));
        }
 
        System.out.println("a_"+a);
        System.out.println("b_"+b);
        System.out.println("c_"+c);
        System.out.println("loss_"+loss);
 
    }
 
    //sigmoid函数
    public static double sigmoid(double x){
        return 1/(1+Math.exp(-x));
    }
}
