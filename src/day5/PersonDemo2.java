package day5;

class Person1
{
	private String name;
	private int age;
	{
		cry();
	}
	Person1(int age)
	{
		this.age = age;
	}
	public void speak()
	{
		System.out.println("name= "+name+","+"age="+this.age);

	}
	public void setName(String name){
		name = name;
	}
	public String getName(){
		return name;
	}
	
	Person1()
	{
		System.out.println("A:name ="+name+", age ="+age);
		
	}
	Person1(String n)
	{
		name = n;
		System.out.println("B:name ="+name+", age ="+age);
	}
		
	Person1(String n,int a)
	{
		name = n;
		age = a;
		System.out.println("C:name ="+name+", age ="+age);
		
	}
	public void cry()
	{
		System.out.println("cry");
	}
	/*是否是同龄人*/
	public boolean compare(Person1 p)
	{
		return this.age==p.age;
	}
}
public class PersonDemo2 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		//Person1 p1 = new Person1();
		//p1.cry();
		//Person1 p2 = new Person1("lisi");
		//Person1 p4 = new Person1("zhangsan");
		//p2.speak();
		//p4.speak();
		//p2.setName("zhangsan");
		//p2.setName("zhangsan1");
		//System.out.println(p2.getName());
		
		Person1 p3 = new Person1("lisi",5);
		Person1 p1 = new Person1(20);
		Person1 p2 = new Person1(25);
		boolean b = p1.compare(p2);
		System.out.println(b);
	}

}
