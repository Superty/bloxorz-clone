#pragma once

#include "globals.hpp"
#include "Graphics.hpp"

enum class TileType { Normal, Fragile, Bridge, Switch, Goal, Empty };

class Board;
class Player;

class Tile {
  public:
	// Tile();
	virtual void draw();
	virtual void stepOn(Player& player, Board& board);
	virtual void activate();
	virtual void update(GLfloat dt);
  
	TileType type;
  Status status;

  static constexpr GLfloat
    LENGTH = 50
  , HEIGHT = 10
  ;

  // protected:
  Tile(TileType o_type, rgb3 o_color, GLint o_row, GLint o_col);
  GLint row, col;
  Cuboid model;
};

class VisibleTile : public Tile {
  public:
    VisibleTile(TileType o_type, rgb3 o_color, GLint o_row, GLint o_col);
    virtual void draw();
};

class NormalTile : public VisibleTile {
  public:
    NormalTile(GLint o_row, GLint o_col);
};

class FragileTile : public VisibleTile {
  public:
    FragileTile(GLint o_row, GLint o_col);
    virtual void stepOn(Player& player, Board& board);
};

class EmptyTile : public Tile {
  public:
	  EmptyTile(GLint o_row, GLint o_col);
    virtual void stepOn(Player& player, Board& board);
};

class GoalTile : public Tile {
  public:
	  GoalTile(GLint o_row, GLint o_col);
    virtual void stepOn(Player& player, Board& board);
};

enum class BridgeState { Expanded, Folded };

class BridgeTile : public VisibleTile {
  public:
  	BridgeTile(GLint o_row, GLint o_col);
  	void init(Direction o_dir, BridgeState o_state);
  	virtual void activate();
  	virtual void update(GLfloat dt);
    virtual void stepOn(Player& player, Board& board);

  private:
    void animateModelTill(GLfloat& attr, GLfloat by, GLfloat tillDegrees);
    Direction dir;
    GLfloat updateTime;
    Status status;
    BridgeState state;
};

class SwitchTile : public VisibleTile {
  public:
    SwitchTile(GLint o_row, GLint o_col);
    void init(vector<pair<int,int>>&& o_bridgeList);
    virtual void draw();
    virtual void stepOn(Player& player, Board& board);

  private:
    static constexpr GLfloat
      BORDER_PADDING = 7
    , SWITCH_HEIGHT = 5
    ;
    Cuboid switchModel;
    vector<pair<int,int>> bridgeList;
};
