class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size(), n = classroom[0].size();

        vector<pair<int,int>> litter;
        int sr, sc;

        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(classroom[i][j]=='S'){
                    sr=i;
                    sc=j;
                }
                else if(classroom[i][j]=='L'){
                    litter.push_back({i,j});
                }
            }
        }

        int k = litter.size();
        int fullMask = (1<<k)-1;

        vector<vector<int>> id(m, vector<int>(n,-1));
        for(int i=0;i<k;i++)
            id[litter[i].first][litter[i].second]=i;

        vector<vector<vector<int>>> best(
            m,
            vector<vector<int>>(n,
                vector<int>(1<<k,-1))
        );

        queue<array<int,5>> q;
        q.push({sr,sc,0,energy,0});

        best[sr][sc][0]=energy;

        int dr[4]={-1,1,0,0};
        int dc[4]={0,0,-1,1};

        while(!q.empty()){
            auto [r,c,mask,e,dist]=q.front();
            q.pop();

            if(mask==fullMask)
                return dist;

            for(int d=0;d<4;d++){
                int nr=r+dr[d];
                int nc=c+dc[d];

                if(nr<0||nr>=m||nc<0||nc>=n)
                    continue;

                if(classroom[nr][nc]=='X')
                    continue;

                if(e==0)
                    continue;

                int ne=e-1;
                int nmask=mask;

                if(id[nr][nc]!=-1)
                    nmask|=(1<<id[nr][nc]);

                if(classroom[nr][nc]=='R')
                    ne=energy;

                if(best[nr][nc][nmask] >= ne)
                    continue;

                best[nr][nc][nmask]=ne;
                q.push({nr,nc,nmask,ne,dist+1});
            }
        }

        return -1;
    }
};