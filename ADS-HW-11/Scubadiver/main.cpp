#include <iostream>
#include <vector>
struct tank{
	int oxygen;
	int nitrogen;
	int weight;
	tank(int o, int n, int w) : oxygen(o), nitrogen(n), weight(w){}
	tank(){
		oxygen = 0; weight = 0; nitrogen = 0;
	}
	friend std::ostream& operator<<(std::ostream& out, tank& a){
		out<<"weight: "<<a.weight<<" O: "<<a.oxygen<<" N: "<<a.nitrogen<<std::endl;
		return out;
	}
	friend std::istream& operator>>(std::istream& in, tank& a){
		in>>a.oxygen;
		in>>a.nitrogen;
		in>>a.weight;
		if (a.oxygen < 1 || a.nitrogen < 1 || a.weight < 1)
			throw std::logic_error("this is seriously fucked up if you take off points if someone doesn't do this");
		else if(a.oxygen > 21 || a.nitrogen > 79 || a.weight > 800)
			throw std::logic_error("haha code go brrrr");
		return in;
	}

};
template <class T> inline T min(T a, T b){
	return (a < b ? a : b);
}

template <class T> inline T max(T a, T b){
	return (a > b ? a : b);
}
int MinWeight(int numcyl, int O, int N, tank*& arr, int*** dp);

int MinWeightInitialize(int numcyl, int O, int N, tank* arr){
	int*** dp = new int**[numcyl+1];
	for(int i = 0; i < numcyl+1; i++){
		dp[i] = new int*[O+1];
		for (int j = 0; j < O+1; j++){
			dp[i][j] = new int[N+1];
			for (int k = 0; k < N+1; k++){
				dp[i][j][k] = -1;
			}
		}
	}
	int output =  MinWeight(numcyl, O, N, arr, dp);
	/* the first thing we do is to go the array at the originally called oxygen and nitrogen values in the last tank.
	 * FIND PATH: consider a trace of the output 3 dimensional array at each "slice" of a tank: there are a few cases:
	 * CASE 1):
	 * the weight values in the same O and N position in the previous tank are the same, so this tank was not included.
	 * CASE 2): the values in the previous tank are not the same:
	 * 	in this case we subtract the oxygen and nitrogen values of the tank we are currently iterating through, add it to our path,
	 * 	then evaluate the 3-d array in the previous array
	 * 			corner cases:
	 * 			negative values: evaluated to zero
	 * 	TERMINATION: double zero in oxygen and nitrogen: solution has already been found.
	 */
	std::cout<<output<<std::endl;
	int cyl = numcyl;
	int Ox = O;
	int Ni = N;
	std::vector<int> path;
	while(cyl > 0 && ( Ox > 0 || Ni > 0)) {
		int w = dp[cyl][Ox][Ni];
		if (w != dp[cyl-1][Ox][Ni]) {
			Ox -= arr[cyl-1].oxygen;
			Ni -= arr[cyl-1].nitrogen;
			Ox = max(Ox, 0);
			Ni = max(Ni, 0);
			path.push_back(cyl-1);
			//std::cout<<"inserting cylinder: "<<cyl-1<<" into path\n";
		}
		cyl--;
	}
	std::reverse(path.begin(), path.end());
	for (auto it = path.begin(); it != path.end(); it++)
		std::cout<<*it +1 <<" ";
	std::cout<<std::endl;

	return output;

}


int MinWeight(int numcyl, int O, int N, tank*& arr, int*** dp){

	if (dp[numcyl][O][N] != -1){
	//std::cout<<"already computed! value is "<<dp[numcyl][O][N]<<std::endl;

		return dp[numcyl][O][N];
	}


	if (O == 0 && N == 0) dp[numcyl][O][N] = 0;
	else if( numcyl == 0){
		dp[numcyl][O][N] = 99999;
	}

	else{
		dp[numcyl][O][N] = min(arr[numcyl-1].weight + MinWeight(numcyl-1, max(O - arr[numcyl-1].oxygen, 0), max(N - arr[numcyl-1].nitrogen, 0), arr, dp),
				MinWeight(numcyl-1, O, N, arr, dp));
	}
	//std::cout<<"consider tank "<<numcyl<<"values follow\n"<<arr[numcyl-1]<<std::endl;
	return dp[numcyl][O][N];
}
//optimization problem: find the maximum
/*
3 36 120
10 25 129
5 50 250
1 45 130
4 20 119
 *
 *
 */
void testcase(){
	using namespace std;
	int t, a;
	cin>>t ;
	cin>>a;
	if(t< 0 || a < 0)
		throw logic_error("JonSnowDies");
	if (t > 21 || a > 79)
		throw logic_error("JotaroDiesInPart6");
	int n;
	cin>>n;
	if (n < 1 || n > 1000)
		throw logic_error("tony stark dies");
	tank cylinders[n];
	for(int i = 0; i < n; i++){
		cin>>cylinders[i];
	}
	MinWeightInitialize(n, t, a, cylinders);


}

int main() {
	using namespace std;

	int c;
	cin>>c;
	try {
		for (int i = 0; i < c; i++)
			testcase();
	}
	catch(std::logic_error& a){
		cout<<"error caught! : "<<a.what();
	}

	return 0;
}
