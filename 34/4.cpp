#pragma GCC optimize(3)
#include<bits/stdc++.h>
using namespace std;
int dp[1001][21000];
int g[1001][21000];//第i个仓库出售花费为j时的最大收益
int base[1001],b[1001][1100],c[1001],tot[1001];//基础花费，每个仓库下有哪些货物，价格多少，数量多少
int maxi[1001];//每个仓库的最大花费
int n,m,v,sum;
int pre[1001][1100];
unordered_map<int,bool>mp;
int pot[1001],tt;//记录有货物的仓库 
bool cmp(int x,int y) {
	return x>y;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>v;
	for(int i=1; i<=n; i++)cin>>base[i]>>c[i];
	for(int j=1; j<=m; j++) {
		int x,y;
		cin>>x>>y;
		++y;
		if(!mp[y]){
			mp[y]=true;
			pot[++tt]=y;
		}
		b[y][++tot[y]]=x;
	}
	sort(pot+1,pot+tt+1);
	for(int i=1; i<=n; i++) {
		if(!mp[i])continue;
		maxi[i]=base[i]+tot[i]*c[i];
		sort(b[i]+1,b[i]+tot[i]+1,cmp);
		sum+=maxi[i];
		for(int j=1; j<=tot[i]; j++) {
			pre[i][j]=pre[i][j-1]+b[i][j];//仓库i卖出j个商品的最理想收入
		}
	}
	for(int i=1; i<=n; i++) {
		//枚举该仓库到底出了多少货
		//只要当前价格足够卖完这些货，卖完这些货就是最优解
		if(!mp[i])continue;
		g[i][maxi[i]]=pre[i][tot[i]];
		int las(maxi[i]),now;
		for(int j=tot[i]-1; j>=1; j--) {
			now=j*c[i]+base[i];
			for(int k=las-1; k>=now; k--) {
				g[i][k]=pre[i][j];
				//cout<<i<<' '<<k<<' '<<g[i][k]<<'\n';
			}
			las=now;
		}
	}
	for(int i=1; i<=tt; i++) {
		//枚举第i个仓库
		for(int k=maxi[pot[i]]; k>=0; k--) {
			for(int j=sum; j>=0; j--) {
				if(j>=k)dp[pot[i]][j]=max(dp[pot[i]][j],max(dp[pot[i-1]][j],dp[pot[i-1]][j-k]+g[pot[i]][k]));
				else dp[pot[i]][j]=dp[pot[i-1]][j];
			}
		}
	}
	int ans(0x3f3f3f3f);
	for(int j=sum; j>=0; j--) {
		if((dp[pot[tt]][j]-j)>=v) {
			ans=min(ans,j);
			continue;
		}
	}
	cout<<ans<<"\n";
}
