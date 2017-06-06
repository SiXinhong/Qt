package day5;

class Person
{
	private int age;
	public void setAge(int a)
	{
		if (a > 0&&a < 130){
			age = a;
		}
		else{
			System.out.println("²»ºÏ·¨");
		}
	}
	public int getAge()
	{
		return age;
	}
	void speak()
	{
		System.out.println("age="+age);
	}
}
public class PersonDemo {
	public static void main(String[] args){
		Person p = new Person();
		//p.age = 20;
		p.setAge(20);
		p.speak();
		Person q = new Person();
		//p.age = 20;
		q.setAge(20);
		q.speak();
	}
	
}
