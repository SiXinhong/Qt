package day5;

class Person3{
	private String name;
	private int age;
	Person3(String name)
	{
		this.name = name;
	}
	Person3(String name,int age)
	{
		
		this(name);
		//this.name = name;
		this.age = age;
	}
	public void speak()
	{
		System.out.println("name="+this.name+","+"age="+age);
	}
}


public class PersonDemo3 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Person3 p = new Person3("lisi",30);
		p.speak();

	}

}
