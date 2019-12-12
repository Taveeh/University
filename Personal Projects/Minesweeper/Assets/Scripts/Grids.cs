using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Grids : MonoBehaviour
{
    public static int latime = 10;
    public static int lungime = 13;
    public static Elements[,] elements = new Elements[latime, lungime];
    public static int[] dx = {0, 1, 1, 1, 0, -1, -1, -1};
    public static int[] dy = {1, 1, 0, -1, -1, -1, 0, 1};
    public static void uncoverMines() {
        foreach (Elements elem in elements)
        {
            if(elem.BOOOOM) {
                elem.loadTexture(0);
            }
        }
    }
    
    public static bool mineAt (int x, int y) {

        if(x >=0 && y >= 0 && x < latime && y < lungime) {
            return elements[x, y].BOOOOM;
        }
        return false;
    }
    public static int bombeVecine(int x, int y) {
        int cnt = 0;
        for (int i = 0; i < 8; i++)
        {
            if(mineAt(x + dx[i], y + dy[i])) ++cnt;
        }
        return cnt;
    }
    public static bool[,] viz = new bool[99, 99];
    public static void Fill(int x, int y) {
            if(viz[x, y]) return;
            if(mineAt(x, y)) return;
            elements[x, y].loadTexture(bombeVecine(x, y));
            if(bombeVecine(x,y) > 0) return;
            viz[x,y] = true;
            if(x < latime - 1) Fill(x + 1, y);
            if(y < lungime - 1) Fill(x, y + 1);
            if(x > 0) Fill(x - 1, y);
            if(y > 0) Fill(x, y - 1);
            if(x < latime - 1 && y < lungime - 1) Fill(x + 1, y + 1);
            if(x < latime - 1 && y > 0) Fill(x + 1, y - 1);
            if(x > 0 && y < lungime - 1) Fill(x - 1, y + 1);
            if(x > 0 && y > 0) Fill(x - 1, y - 1);
    }
    public static bool EndGame () {
        foreach (Elements elem in elements)
        {
            if(elem.eNeApasat() && !elem.BOOOOM) {
                return false;
            }
        }
        return true;
    }
    
}
