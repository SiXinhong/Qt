package day5;

class Car
{
	String color = "ºìÉ«";
	int num = 4;
	void run()
	{
		System.out.println(color +".."+num);
	}
}
public class CarDemo {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Car c = new Car();
		c.color = "blue";
		c.run();
		
		Car c1 = c;
		c1.color = "green";
		c.run();

	}

}
