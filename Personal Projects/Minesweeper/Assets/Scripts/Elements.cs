using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Elements : MonoBehaviour
{
    //Bomb = true
    public bool BOOOOM;

    //Sprite for default
    public Sprite defaultTexture;
    //Array for the other sprites
    public Sprite[] emptyTextures;

    //Sprite for mine
    public Sprite mineTexture;

    //Sprite for flag
    public Sprite flagTexture;
    
    //Random value to first button
    void Start () {
        BOOOOM = Random.value < 0.15;

        //Coordonate
        int x = (int)transform.position.x;
        int y = (int)transform.position.y;
        Grids.elements[x, y] = this;
    }
    //Void in order to load the texture of a mine or the number
    public void loadTexture (int bombeVecine) {
        if(BOOOOM) {
            GetComponent<SpriteRenderer>().sprite = mineTexture;
        }else {
            GetComponent<SpriteRenderer>().sprite = emptyTextures[bombeVecine];
        }
    }
    public void putFlag () {
        GetComponent<SpriteRenderer>().sprite = flagTexture;
    }

    public void removeFlag() {
        GetComponent<SpriteRenderer>().sprite = defaultTexture;
    }
    public bool areSteag() {
        return GetComponent<SpriteRenderer>().sprite.texture.name == "Minesweeper_flag.svg";
    }

    //If the sprite is covered, it will be the default one
    public bool eNeApasat () {
        return GetComponent<SpriteRenderer>().sprite.texture.name == "Default";
    }
    private void OnMouseOver() {
        if(Input.GetMouseButton(1)) {
            if(areSteag()) {
                removeFlag();
            }else {
                putFlag();
            }
            System.Threading.Thread.Sleep(250);
        }
    }
    void OnMouseUp () {
        
        if (BOOOOM) {
            
            print ("See you later, aligator");
            Grids.uncoverMines ();
            //Application.Quit;
        }else {
            
            int x = (int)transform.position.x;
            int y = (int)transform.position.y;
            loadTexture(Grids.bombeVecine(x, y));
            Grids.Fill(x, y);
            if(Grids.EndGame()) {
                print("Great job, buddy!!");
                //Application.Quit;
            }
            
        }
    }
    public void Update() {
        if(Input.GetKeyDown(KeyCode.Escape)) {
            Application.Quit();
        }
        if(Input.GetKeyDown(KeyCode.R)) {
            for(int i = 0; i < 99; ++i) {
                for(int j = 0; j < 99; j++) {
                    Grids.viz[i, j] = false;
                }
            }
            
            SceneManager.LoadScene(SceneManager.GetActiveScene().name);
        }
    }
    
}
