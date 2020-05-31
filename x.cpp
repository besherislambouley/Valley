/*
 * let node a is the lower node from the edge , node b is the given node , dis [node] = the distance from the root to node
 * the answer is "escaped" when a is not an ancestor of b 
 * now we are left with 2 options 
 * the nearest node is in the subtree of node b ( can be found easily ) 
 * otherwise then we have to go up tell a specific node then go down to the shop
 * the cost then is dis [b] + dis [Shop] - 2 * dis [lca(Shop,b)] so we store in each node -2*dis[node] + dis [ Min ( shop ) ]
 * and we found the best answer using binary lifting
*/
#define fast ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <bits/stdc++.h>
using namespace std;
#define sqr 400
#define mp make_pair
#define mid (l+r)/2
#define Le Node * 2 
#define Ri Node * 2 + 1 
#define pb push_back
#define ppb pop_back
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound
#define ins insert
#define era erase
#define C continue
#define mem(dp,i) memset(dp,i,sizeof(dp))
#define mset multiset
#define all(x) x.begin(), x.end()
#define gc getchar_unlocked
typedef long long ll;
typedef short int si;
typedef long double ld;
typedef pair<int,int> pi;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pi> vpi;
typedef vector<pll> vpll;
typedef pair<double,ll>pdi;
const ll inf=1e18;
const ll Mod=1e9+7;
const ld pai=acos(-1);
ll n , m , q , Root ;
pll E [100009] ;
vpll v [100009] ;
ll Dis [100009] , w [100009] , Dp [100009][20] , Mn [100009][20] , Best [100009] , Yes [100009] ;
void Fill ( ll Node , ll p , ll Sum ) {
	Dp [Node][0] = p ;
	w  [Node] = w [p] + 1 ;
	Dis[Node] = Sum ;
	Best [Node] = ( Yes [Node] ? Dis [Node] : inf ) ;
	for ( auto u : v [Node] ) {
		if ( u.fi == p ) C ;
		Fill ( u.fi , Node , Sum + u.se ) ;
		Best [Node] = min ( Best [Node] , Best [u.fi] ) ;
	}
}
ll Check ( ll a , ll b ) {
	if ( w [a] < w [b] ) swap ( a , b ) ;
	ll l = w [a] - w [b] ;
	for ( ll i = 0 ; i < 20 ; i ++ ) {
		if ( ( l & ( 1 << i ) ) ) a = Dp [a][i] ;
	}
	return ( a == b ) ;
}
ll Query ( ll a , ll b ) { 
	if ( w [a] < w [b] ) swap ( a , b ) ;
        ll l = w [a] - w [b] ;
	ll ans = Best [a] ; 
        for ( ll i = 0 ; i < 20 ; i ++ ) {
                if ( ( l & ( 1 << i ) ) ) {
			ans = min ( ans , Mn [a][i] ) ;
			a = Dp [a][i] ;
		}
        }
	return ans ;
}
int main () {
	scanf("%lld%lld%lld%lld",&n,&m,&q,&Root) ;
	Root -- ;
	for ( int i = 0 ; i < n - 1 ; i ++ ) {
		ll a , b , c ;
		scanf("%lld%lld%lld",&a,&b,&c) ;
		a -- , b -- ;
		v [a] .pb ( { b , c } ) ;
		v [b] .pb ( { a , c } ) ;
		E [i] = { a , b } ; 
	}
	for ( ll i = 0 ; i < m ; i ++ ) {
		ll x ;
		scanf("%lld",&x) , x -- ;
		Yes [x] = 1 ;
	}
	Fill ( Root , Root , 0 ) ;
	for ( ll Node = 0 ; Node < n ; Node ++ ) {
		Best [Node] += -2 * Dis [Node] ;
	}
	for ( int Node = 0 ; Node < n ; Node ++ ) {
		Mn [Node][0] = min ( Best [Node] , Best [ Dp [Node][0] ] ) ;
	}
	for ( int j = 1 ; j < 20 ; j ++ ) {
		for ( int i = 0 ; i < n ; i ++ ) {
			Dp [i][j] = Dp [ Dp [i][j-1] ][j-1] ;
			Mn [i][j] = min ( Mn [i][j-1] , Mn [ Dp [i][j-1] ][j-1] ) ;
		}
	}
	for ( int i = 0 ; i < n - 1 ; i ++ ) {
		if ( w [ E [i].fi ] > w [ E [i] .se ] ) swap ( E [i].fi , E [i] .se ) ;
	}
	while ( q -- ) {
		int e , b ;
		scanf("%d%d",&e,&b) ;
		e -- , b -- ;
		int a = E [e] .se ;
		if ( Check ( a , b ) && w [a] <= w [b] ) {
			ll x = min ( Query ( a , b ) , Best [b] ) + Dis [b] ;
			if ( x >= 1e17 ) puts("oo");
			else printf("%lld\n",x) ; 
		}
		else puts("escaped"); 
	}
}
