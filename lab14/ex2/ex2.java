import java.util.concurrent.locks.*;
import java.lang.Thread;

public class ex2 {
	public static Warehouse wh = new Warehouse();
	
	public static void main(String[] args) {
		job1 j1 = new job1();
		job2 j2 = new job2();
		Thread th1 = new Thread(j1);
		Thread th2 = new Thread(j2);
		
		th1.start();
		th2.start();
		
		try {
			th1.join();
			th2.join();
		}
		catch(InterruptedException e) {} 
	}

	static class job1 implements Runnable {
		public void run() {
			for(;;) {
				wh.setProduct();
			}
		}
	}

	static class job2 implements Runnable {
		public void run() {
			for(;;) {
				wh.getProduct();
			}
		}
	}
}

class Warehouse {
	private Lock lock = new ReentrantLock();
	private Condition threadCond = lock.newCondition();
	
	private int product = 0;
	
	public void setProduct() {
		lock.lock();
		try {
			while(product == 10) {
				try {
					System.out.println("FULL");
					threadCond.await();
				}
				catch(InterruptedException e) {e.printStackTrace();}
			}
			product++;
			System.out.println("Product +1 / Amount = "+product);
			
			threadCond.signal();
		}
		finally {
			lock.unlock();
		}
	}
	
	public void getProduct() {
		lock.lock();
		try {
			while(product == 0) {
				try {
					System.out.println("EMPTY");
					threadCond.await();
				}
				catch(InterruptedException e) {e.printStackTrace();}
			}
			product--;
			System.out.println("Product -1 / Amount = "+product);
			
			threadCond.signal();
		}
		finally {
			lock.unlock();
		}
	}
}
