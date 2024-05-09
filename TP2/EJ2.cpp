#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};
vector<pair<int, int>> res;

struct Node {
    int x;
    int y;
    int t;
};

int N,M;
std::queue<Node> q;
vector<vector<int>> matriz;
vector<vector<bool>> visited;

int bfs(Node& v, Node& target, int start_time) {
    q.push(v);
    visited = vector<vector<bool>>(N,
                                   vector<bool>(M,
                                                false));
    visited[v.x][v.y] = true;

    while (!q.empty()) {
        Node v1 = q.front();
        int nT = v1.t + 1;
        q.pop();

        if (v1.x == target.x && v1.y == target.y)
            return nT - 1 + start_time;

        for (int i = 0; i < 4; ++i) {
            int xx = v1.x + dx[i];
            int yy = v1.y + dy[i];

            if (xx < 0 or xx >= N)
                continue;
            if(yy < 0 or yy >= M)
                continue;
            if(visited[xx][yy])
                continue;
            if(nT+start_time >= matriz[xx][yy] && matriz[xx][yy] != 0)
                continue;

            visited[xx][yy] = true;
            Node n = {xx, yy, nT};
            q.push(n);
        }
    }

    return -1;
}

int main() {
    int t;
    cin >> t;
    while (t > 0) {
        q = queue<Node>();

        cin >> N >> M;
        int p;

        matriz = vector<vector<int>>(N, vector<int>(M));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                cin >> p;
                matriz[i][j] = p;
            }
        }

        // ---- Cords -----
        int x, y;
        cin >> x >> y;
        Node hospital = {x, y, 0};
        cin >> x >> y;
        Node persona  = {x, y, 0};

        int path_1 = bfs(hospital, persona,0);
        q = queue<Node>();

        int path_2 = bfs(persona, hospital,path_1);
        res.emplace_back(path_1, path_2);
        t--;
    }

    for (auto r : res) {
        if (r.first == -1 or r.second == -1) {
            cout << "IMPOSIBLE" << endl;
        } else {
            cout << r.first << " " << r.second << endl;
        }
    }
}