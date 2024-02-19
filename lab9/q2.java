public class q2 {
	public static int cnt = 0;
	public static void main(String argv[]) {
		int iter = 250000;
		ShareData s1 = new ShareData(iter);
		Thread t1 = new Thread(s1);
		ShareData s2 = new ShareData(iter);
		Thread t2 = new Thread(s2);
		ShareData s3 = new ShareData(iter);
		Thread t3 = new Thread(s3);
		ShareData s4 = new ShareData(iter);
		Thread t4 = new Thread(s4);
		
		t1.start();
		t2.start();
		t3.start();
		t4.start();
		try{
			t1.join();
			t2.join();
			t3.join();
			t4.join();
		}catch(InterruptedException ie){
			System.err.println(ie);
		}

		System.out.println("Final count value: "+cnt);
	}
}

class ShareData implements Runnable{
	int i;
	public ShareData(int iter) {
		i = iter;
	}
	public void run() {
		for(int n = 0; n < i; n++) {
			q2.cnt++;
		}
		System.out.println("Thread name is Thread-"+Thread.currentThread().getName()+", count is: "+q2.cnt);
	}
}
