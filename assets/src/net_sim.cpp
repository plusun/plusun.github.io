#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

const int MAX_SEQ_NUM = 10;

struct package
{
	int seq_num;
	string payload;
};

class buffer
{
	public:

	buffer()
	{
		circle = vector< package* >( MAX_SEQ_NUM, nullptr );
		head = 0;
	}

	void push( package* pkg )
	{
		if ( circle[pkg->seq_num] != nullptr )
			circle[pkg->seq_num] = pkg;
	}

	string get_message()
	{
		string msg = "";
		while ( circle[head] != nullptr )
		{
			msg = msg + circle[head]->payload;
			delete circle[head];
			circle[head] = nullptr;
			head++;
		}
		return msg;
	}

	~buffer()
	{
		for ( int i=0; i<circle.size(); i++ )
			if ( circle[i]!=nullptr )
			{
				delete circle[i];
				circle[i] = nullptr;
			}
	}

	private:

	vector< package* > circle;
	int head;

};

package* from_lower_layer()
{
	package* pkg = new package;
	pkg->seq_num = rand()%MAX_SEQ_NUM;
	pkg->payload = "WTF";
	return pkg;
}

void to_upper_layer( string msg )
{
	/* you never know */
}

int main()
{
	buffer b;

	for ( int i = 0; i < 100; i++ )
	{
		package* pkg = from_lower_layer();
		b.push( pkg );
		string msg = b.get_message();
		to_upper_layer( msg );
	}

}

