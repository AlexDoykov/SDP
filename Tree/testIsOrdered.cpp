#include<iostream>
#include<vector>
#include<queue>
using namespace std;
int n;
vector<int>l, r;
 
bool order(int root){
    if(l[root]==-1 && r[root]==-1)return 1;
    if(l[root]==-1)return order(r[root]);
    if(r[root]==-1)return order(l[root]);
    if(order(l[root]) && l[root]<root && order(r[root]) && r[root]>root)return 1;
    else return 0;
}
 
int main ()
{
    int root;
    queue<int>q;
    cin>>n;
    cout<<"If there is no child node: -1\n";
    cout<<"root: ";cin>>root;
    q.push(root);
    int x, y, t;
    l.assign(n+1, -1);
    r.assign(n+1, -1);
    for(int i=1; i<n; i++){
        t=q.front();
        q.pop();
        cout<<t<<": "; 
        cin>>x>>y;
        l[t]=x;
        r[t]=y;
        if(x!=-1)q.push(x);
        if(x!=-1)q.push(y);
    }
    cout<<order(root)<<endl;
 
 
    return 0;
}