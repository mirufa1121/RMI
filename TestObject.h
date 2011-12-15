class TestObject {
	
	private:
		int testInt;
		double testDouble;
		char testChar;

	public:
		
		TestObject();
		TestObject(int n, double d, char c);

		int getTestInt();
		double getTestDouble();
		char getTestChar();

		void setTestInt(int n);
		void setTestDouble(double d);
		void setTestChar(char c);
};