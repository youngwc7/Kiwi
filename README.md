# Kiwi Chess Engine - IN PROGRESS -> LATE PHASE 2. 

A C++ chess engine built from scratch with SFML GUI, classical search, and a planned Neural Network engine.

---

## Project Structure

```
Kiwi/
├── src/
│   ├── main.cpp
│   ├── guiboard.cpp
│   ├── bitboard.cpp
│   └── include/
│       ├── guiboard.hpp
│       ├── bitboard.hpp
│       ├── piece.hpp
│       └── constants.hpp
├── images/          ← chess piece PNGs (not tracked by git)
├── CMakeLists.txt
├── build.sh
└── README.md
```

---

## Dependencies

- **SFML 2.5.1** — GUI rendering
- **CMake 3.16+** — build system
- **C++17**

Install SFML on Ubuntu:
```bash
sudo apt-get install libsfml-dev
```

---

## Build & Run

```bash
./build.sh        # build
./build.sh clean  # clean build folder
./Kiwi            # run
```

---

## Development Roadmap

### [DONE] Phase 1 — GUI Foundation

**Window & Rendering**
- SFML 2.5.1 window with fixed 800x800 resolution
- 8x8 chessboard rendered using `sf::RectangleShape` with alternating light/dark squares
- Chess piece sprites loaded from PNG images into `sf::Texture` / `sf::Sprite` maps
- Pieces scaled to fit square size at load time — no per-frame scaling

**Input Handling**
- `MouseButtonReleased` events to avoid multi-fire click issues
- `pixelToSquare()` converts pixel coordinates to square index
- Click state machine: IDLE → SELECTED → MOVE/DESELECT

**Highlights**
- Green highlight for selected square
- Blue highlight for last move destination
- Highlights drawn between squares and pieces in render order

**Architecture**
- `GuiBoard` class — strictly handles rendering and input, no game logic
- `chessboardString[8][8]` — string-based board state for rendering (`"wP"`, `"bK"`, `""`)
- `draw()` — called every frame: squares → highlights → pieces
- `moveDraw()` — updates `chessboardString` and clears selection state
- `handleClick()` — manages selection, deselection, and move initiation

---

### [IN PROGRESS] Phase 2 — Chess Engine (Rule Layer)

**Board Representation** ✅
- `Bitboard` class with 12 piece bitboards (one per piece type per color)
- Combined aggregate bitboards: `whitePieces`, `blackPieces`, `board`, `vacancy`
- `piece.hpp` — `PieceType`, `Color`, `Piece` enums with bitmask encoding
- Core mutations: `setPiece`, `removePiece`, `movePiece`
- `bitboardToChessboardString` — syncs bitboard state to GUI layer
- `GuiBoard` holds a `Bitboard&` reference for communication

**Position / GameState Class**
- Wraps `Bitboard` with game metadata encoded in a `uint8_t` state flag:
  - Castling rights: white/black kingside and queenside
  - En passant availability and target file (`uint8_t enPassantFile`)
  - Whose turn (white/black)
- Half move clock for 50-move rule (`uint8_t halfMoveClock`)
- Full move counter (`uint16_t fullMoveCount`)
- FEN string support — load any position for testing

**Move Encoding**
- `Move` struct encoded in a single `uint32_t`:
  ```
  bits  0-5:  source square      (0-63)
  bits  6-11: destination square (0-63)
  bits 12-15: moving piece       (Piece enum)
  bits 16-19: captured piece     (Piece enum)
  bits 20-23: move flags
  ```
- Move flags (`MoveFlag` enum):
  ```
  QUIET      = 0b0000
  CAPTURE    = 0b0001
  EN_PASSANT = 0b0010
  CASTLING   = 0b0100
  PROMOTION  = 0b1000
  ```

**Move Generation (`MoveGen` class)**
- Pseudo-legal move generation per piece type:
  - Pawns: single push, double push, captures, en passant
  - Knights: precomputed attack tables
  - Bishops/Rooks/Queens: sliding piece attack generation
  - King: precomputed attack tables + castling
- Legal move filtering: remove moves that leave king in check
- `MoveList` — fixed-size array of `Move` passed to move generation

**Game State Detection**
- Check detection via attack maps
- Checkmate: no legal moves + in check
- Stalemate: no legal moves + not in check
- Draw conditions: 50-move rule, threefold repetition, insufficient material

---

### Phase 3 — Classical Engine

**Move Application**
- `makeMove()` / `unmakeMove()` — fast make/unmake using XOR trick:
  ```cpp
  bb ^= (srcMask | destMask);  // clears src and sets dest in one operation
  ```
- Move history stack for unmake
- Zobrist hashing for position identification

**Search**
- Minimax with alpha-beta pruning
- Iterative deepening — search depth 1, 2, 3... until time runs out
- Quiescence search — extend search at captures to avoid horizon effect
- Transposition table — cache previously evaluated positions via Zobrist hash
- Move ordering to maximize alpha-beta cutoffs:
  - PV move first
  - Captures ordered by MVV-LVA (Most Valuable Victim, Least Valuable Attacker)
  - Killer moves
  - History heuristic

**Evaluation**
- Material counting via `PieceType` values
- Piece-square tables — positional bonuses per piece per square
- King safety
- Pawn structure (doubled, isolated, passed pawns)

**Threading**
- Engine runs on a separate thread to avoid blocking the GUI at 60fps
- Communication via `std::atomic<bool>` flag and shared `Move` result
- Main thread: render loop → draw → handle input
- Engine thread: search → evaluate → return best move

---

### Phase 4 — Neural Network Engine (Overview)

Replace or augment the classical evaluator with a neural network, trained via self-play in the style of AlphaZero.

- **Input**: board position encoded from bitboards into input tensors
- **Network**: policy head (move probabilities) + value head (position evaluation)
- **Training**: self-play games → MCTS guided by NN → update weights
- **Integration**: NN inference replaces or supplements the classical evaluation function
- Bitboard representation maps naturally to NN input tensors

---

## Square Indexing Convention

Bitboard uses LSB-first (standard):
```
a1 = 0,  b1 = 1,  ...,  h1 = 7
a2 = 8,  b2 = 9,  ...,  h2 = 15
...
a8 = 56, b8 = 57, ...,  h8 = 63
```

GUI renders top-down (rank 8 at top), conversion handled by `bitboardToChessboardString`.

---

## Piece Encoding (`piece.hpp`)

Pieces are encoded as a single `uint8_t` combining `Color` and `PieceType` via bitmasking:

```
bits 0-5: piece type (PAWN=1, KNIGHT=2, BISHOP=4, ROOK=8, QUEEN=16, KING=32)
bits 6-7: color      (WHITE=0b01000000, BLACK=0b10000000)
```

Helper functions: `isWhite(p)`, `isBlack(p)`, `isEmptyPiece(p)`, `getType(p)`, `pieceToChessString(p)`
