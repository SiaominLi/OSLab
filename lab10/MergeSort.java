import java.util.concurrent.*;
import java.util.*;

public class MergeSort extends RecursiveAction {
	int low;
	int high;
	int arr[];

	MergeSort(int[] arr, int low, int high) {
		this.arr = arr;
		this.low = low;
		this.high = high;
	}

	protected void compute() {
		if(low < high) {
			int mid = (low+high) / 2;
			MergeSort m1 = new MergeSort(arr, low, mid);
			MergeSort m2 = new MergeSort(arr, mid+1, high);
			invokeAll(m1, m2);
			merge(arr, low, mid, high);
		}
	}

	static void merge(int[] arr, int low, int mid, int high) {
		int[] aux = new int[arr.length];
		for(int i = low; i <= high; i++) {
			aux[i] = arr[i];
		}

		int i = low, j = mid+1, k = low;
		while(i <= mid && j <= high) {
			if(aux[i] <= aux[j]) {
				arr[k] = aux[i];
				i++;
			}
			else {
				arr[k] = aux[j];
				j++;
			}
			k++;
		}
		while(i <= mid) {
			arr[k] = aux[i];
			i++;
			k++;
		}
		while(j <= high) {
			arr[k] = aux[j];
			j++;
			k++;
		}
	}

	public static void main(String args[]) {
		int[] arr = new int[100];
		Random rand = new Random();
		System.out.println("Before sort:");
		for(int i = 0; i < 100; i++) {
			arr[i] = rand.nextInt(100);
			System.out.println(arr[i]);
		}

		ForkJoinTask <?> task = new MergeSort(arr, 0, arr.length-1);
		ForkJoinPool pool = new ForkJoinPool();
		pool.invoke(task);

		System.out.println("After sort:");
		for(int i = 0; i < 100; i++) {
			System.out.println(arr[i]);
		}
	}
}
