// Aniket Choudhary  
#include <bits/stdc++.h>
#include<cstdlib>
using namespace std;

void FCFS(int arr[], int head,int size)
{
    int seek_count = 0;
    int distance, cur_track;
    cout<<"0 "<<head<<" "<<0<<endl;
    for (int i = 0; i < size; i++) {
        cur_track = arr[i];

        distance = abs(cur_track - head);

        seek_count += distance;

        head = cur_track;
        cout<<(i+1)<<" "<<arr[i]<<" "<<seek_count<<endl;
    }
}

void SCAN(int arr[], int head, string direction,int size, int disk_size)
{
    cout<<"0 "<<head<<" "<<0<<endl;
	int seek_count = 0;
	int distance, cur_track;
	vector<int> left, right;
	vector<int> seek_sequence;
	vector<int> dis;


	if (direction == "left")
		left.push_back(0);
	else if (direction == "right")
		right.push_back(disk_size - 1);

	for (int i = 0; i < size; i++) {
		if (arr[i] < head)
			left.push_back(arr[i]);
		if (arr[i] > head)
			right.push_back(arr[i]);
	}

	std::sort(left.begin(), left.end());
	std::sort(right.begin(), right.end());


	int run = 2;
	while (run--) {
		if (direction == "left") {
			for (int i = left.size() - 1; i >= 0; i--) {
				cur_track = left[i];

				seek_sequence.push_back(cur_track);

				distance = abs(cur_track - head);

				seek_count += distance;
				dis.push_back(seek_count);

				head = cur_track;
			}
			direction = "right";
		}
		else if (direction == "right") {
			for (int i = 0; i < right.size(); i++) {
				cur_track = right[i];
				seek_sequence.push_back(cur_track);

				distance = abs(cur_track - head);

				seek_count += distance;
				dis.push_back(seek_count);

				head = cur_track;
			}
			direction = "left";
		}
	}
	for (int i = 0; i < seek_sequence.size(); i++) {
		cout<<(i+1)<<" "<<seek_sequence[i]<<" "<<dis[i]<<endl;
	}
}

void CSCAN(int arr[], int head,int size, int disk_size)
{
    cout<<"0 "<<head<<" "<<0<<endl;
	int seek_count = 0;
	int distance, cur_track;
	vector<int> left, right;
	vector<int> seek_sequence;
	vector<int> dis;

	left.push_back(0);
	right.push_back(disk_size - 1);

	for (int i = 0; i < size; i++) {
		if (arr[i] < head)
			left.push_back(arr[i]);
		if (arr[i] > head)
			right.push_back(arr[i]);
	}

	std::sort(left.begin(), left.end());
	std::sort(right.begin(), right.end());

	for (int i = 0; i < right.size(); i++) {
		cur_track = right[i];
		seek_sequence.push_back(cur_track);

		distance = abs(cur_track - head);

		seek_count += distance;
		dis.push_back(seek_count);

		head = cur_track;
	}

	head = 0;

	seek_count += (disk_size - 1);

	for (int i = 0; i < left.size(); i++) {
		cur_track = left[i];

		seek_sequence.push_back(cur_track);

		distance = abs(cur_track - head);

		seek_count += distance;
		dis.push_back(seek_count);

		head = cur_track;
	}
	for (int i = 0; i < seek_sequence.size(); i++) {
		cout<<(i+1)<<" "<<seek_sequence[i]<<" "<<dis[i]<<endl;
	}
}

void calculatedifference(int request[], int head,
						int diff[][2], int n)
{
	for(int i = 0; i < n; i++)
	{
		diff[i][0] = abs(head - request[i]);
	}
}

int findMIN(int diff[][2], int n)
{
	int index = -1;
	int minimum = 1e9;

	for(int i = 0; i < n; i++)
	{
		if (!diff[i][1] && minimum > diff[i][0])
		{
			minimum = diff[i][0];
			index = i;
		}
	}
	return index;
}

void shortestSeekTimeFirst(int request[],int head, int size)
{
	if (size == 0)
	{
		return;
	}

	int diff[size][2] = { { 0, 0 } };

	int seekcount = 0;

    vector<int> dis;
    dis.push_back(seekcount);

	int seeksequence[size + 1] = {0};

	for(int i = 0; i < size; i++)
	{
		seeksequence[i] = head;
		calculatedifference(request, head, diff, size);
		int index = findMIN(diff, size);
		diff[index][1] = 1;

		seekcount += diff[index][0];
		dis.push_back(seekcount);

		head = request[index];
	}
	seeksequence[size] = head;

	for(int i = 0; i <= size; i++)
	{
		cout<<i<<" "<<seeksequence[i]<<" "<<dis[i]<<"\n";
	}
}

int main()
{
  label1:
  cout<<"DISK SCHEDULING ALGORITHMS IMPLEMENTATION \n";
  int disk_size;
  cout<<"\nEnter disk Size:\n";
  cin>>disk_size;
  int n;
  cout<<"\nEnter size of sequence to be entered: \n";
  cin>>n;
  cout<<"\nEnter the Sequence: \n";
  int proc[n];
  cout<<"\nEnter "<<n<<" Values: ";
	for(int i=0;i<n;i++)
  {
    cout<<endl;
    cin>>proc[i];
  }
  int head;
  cout<<"\nEnter Head Value: \n";
  cin>>head;
  int mm;
  label:
  cout<<"\nNow, Choose which disk scheduling algorithm you want to run: \n";
  cout<<"---Press 1 for Shortest Seek Time First Algorithm \n";
  cout<<"---Press 2 for C-SCAN Algorithm \n";
  cout<<"---Press 3 for SCAN Algorithm \n";
  cout<<"---Press 4 for First Come First Serve Algorithm \n";
  cout<<"---Press 5 for Entering New Data\n";
  cout<<"---Press 6 for EXIT\n";
  cin>>mm;
  switch (mm) {
  case 1:
    cout<<"\nSSTF Algorithm\n";
	  shortestSeekTimeFirst(proc, head, n);
	  goto label;
    break;
  case 2:
    cout<<"\nCSCAN Algorithm\n";
	  CSCAN(proc,head,n,disk_size);
	  goto label;
    break;
  case 3:
    cout<<"\nSCAN Algorithm\n";
    int dir;
    cout<<"Press 1 if you want to traverse Left in SCAN Algorithm, else Press 2 for traversing Right: ";
    cin>>dir;

   switch(dir){
    case 1:
      SCAN(proc,head,"left",n,disk_size);
      break;
    case 2:
      SCAN(proc,head,"right",n,disk_size);
      break;
   }
   goto label;
   break;
  case 4:
    cout<<"\nFCFS Algorithm\n";
	  FCFS(proc,head,n);
	  goto label;
    break;
  case 5:
    system("cls");
    goto label1;
    break;
  case 6:
    system("cls");
    break;
  }
	return 0;
}
