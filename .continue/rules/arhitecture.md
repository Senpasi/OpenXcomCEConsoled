# Project Architecture

This is a c++ application, opensource clone of X-COM: UFO Defense (1994)
Fork of https://github.com/MeridianOXC/OpenXcom

- .h files of dependencies in `deps/include`, dll libs in `deps/lib/x64`
- `src/Basescape` - control bases, soldiers, crafts, researching, manufacturing, setting equipment for transport, etc
- `src/Battlescape` - control during missions
- `src/Engine` - components responsible for rendering as well as timers and main loop
- `src/Geoscape` - control global view, speed, processing researches, etc
- `src/Interface` - separate interface elements (windows, buttons, labels, etc)
- `src/Menu` - main menu, options, etc
- `src/Mod` - modifications control (rules)
- `src/Savegame` - something like models in other project, data object what saved betwine game save and load
- `src/StreamerConsole` - components for interaction with streamer console
- `src/Ufopaedia` - ufopaedia for players inside game
- `src/main.cpp` - input point of game


## Basescape Module

The Basescape module handles all base-related operations including base management, soldier management, craft management, research, manufacturing, and equipment management. Key components include:


### Base Management
- `BasescapeState` - Main state for base management
- `BaseView` - Base view component
- `MiniBaseView` - Mini base view component
- `BaseInfoState` - Base information display
- `BuildFacilitiesState` - Building new facilities
- `PlaceFacilityState` - Placing facilities
- `PlaceLiftState` - Managing base lift placement
- `DismantleFacilityState` - Removing facilities
- `PlaceStartFacilityState` - Initial facility placement
- `SelectStartFacilityState` - Selecting starting facilities

### Soldier Management
- `SoldiersState` - Main soldier management state
- `SoldierInfoState` - Individual soldier information
- `SoldierRankState` - Soldier rank management
- `SoldierArmorState` - Soldier equipment management
- `SoldierBonusState` - Soldier bonuses and stats
- `SoldierAvatarState` - Soldier avatar management
- `SoldierMemorialState` - Soldier memorial
- `SoldierDiaryLightState` - Light soldier diary view
- `SoldierDiaryMissionState` - Mission-specific soldier diary
- `SoldierDiaryOverviewState` - Soldier diary overview
- `SoldierDiaryPerformanceState` - Soldier performance diary
- `SoldierTransformationState` - Soldier transformation management
- `SoldierTransformationListState` - List of soldier transformations
- `SackSoldierState` - Dismissing soldiers

### Craft Management
- `CraftsState` - Main craft management state
- `CraftInfoState` - Individual craft information
- `CraftEquipmentState` - Craft equipment management
- `CraftArmorState` - Craft armor management
- `CraftWeaponsState` - Craft weapon management
- `CraftSoldiersState` - Soldier assignment to crafts
- `CraftPilotsState` - Pilot management
- `CraftPilotSelectState` - Pilot selection
- `CraftEquipmentLoadState` - Loading equipment onto crafts
- `CraftEquipmentSaveState` - Saving craft equipment configurations

### Research Management
- `ResearchState` - Main research management state
- `ResearchInfoState` - Individual research project information
- `GlobalResearchState` - Global research management
- `GlobalResearchDiaryState` - Research diary
- `TechTreeSelectState` - Technology tree selection
- `TechTreeViewerState` - Technology tree visualization
- `NewResearchListState` - New research project list

### Manufacturing
- `ManufactureState` - Main manufacturing state
- `ManufactureInfoState` - Individual manufacturing project information
- `GlobalManufactureState` - Global manufacturing management
- `ManufactureStartState` - Starting manufacturing projects
- `NewManufactureListState` - New manufacturing project list
- `ManufactureDependenciesTreeState` - Manufacturing dependency visualization

### Item and Equipment Management
- `StoresState` - Item/stores management
- `PurchaseState` - Purchasing items
- `SellState` - Selling items
- `TransferItemsState` - Item transfers between bases
- `TransferBaseState` - Base transfers
- `TransferConfirmState` - Transfer confirmation
- `ItemLocationsState` - Item location tracking

### Alien Containment
- `GlobalAlienContainmentState` - Global alien containment management
- `ManageAlienContainmentState` - Alien containment management

### Cost Management
- `MonthlyCostsState` - Monthly cost calculations and display

### Utility
- `SoldierSortUtil` - Utility for sorting soldiers


## Battlescape Module

The Battlescape module handles all in-mission combat and tactical gameplay. Key components include:

### Core Battlescape Systems
- `BattlescapeState` - Main state for battlescape operations
- `BattlescapeGame` - Core game logic and management
- `BattleState` - Battle state management
- `BattlescapeGenerator` - Map and mission generation
- `BattlescapeMessage` - Message handling system

### Map and Environment
- `Map` - Game map representation
- `TileEngine` - Tile-based engine for rendering and interaction
- `Camera` - Camera system for viewing the battlefield
- `MiniMapView` - Mini-map view
- `Position` - Position and coordinate system
- `Pathfinding` - Pathfinding algorithms
- `PathfindingNode` - Pathfinding node structures
- `PathfindingOpenSet` - Open set for pathfinding

### Units and Characters
- `UnitSprite` - Unit sprite rendering
- `UnitDieBState` - Unit death state
- `UnitFallBState` - Unit falling state
- `UnitTurnBState` - Unit turning state
- `UnitWalkBState` - Unit walking state
- `UnitPanicBState` - Unit panic state
- `AlienInventory` - Alien inventory management
- `AlienInventoryState` - Alien inventory state

### Combat and Actions
- `ActionMenuState` - Action menu interface
- `ActionMenuItem` - Action menu items
- `MeleeAttackBState` - Melee attack state
- `Projectile` - Projectile system
- `ProjectileFlyBState` - Projectile flight state
- `Explosion` - Explosion system
- `ExplosionBState` - Explosion battle state
- `PrimeGrenadeState` - Grenade priming state
- `PsiAttackBState` - Psionic attack state

### Inventory and Equipment
- `Inventory` - Inventory system
- `InventoryState` - Inventory state
- `InventoryLoadState` - Inventory loading state
- `InventorySaveState` - Inventory saving state
- `InventoryPersonalState` - Personal inventory state
- `ExtendedInventoryLinksState` - Extended inventory links
- `AlienInventory` - Alien inventory management
- `ItemSprite` - Item sprite rendering

### Scanning and Detection
- `ScannerState` - Scanner system
- `ScannerView` - Scanner view interface

### Medical System
- `MedikitState` - Medikit system
- `MedikitView` - Medikit view interface

### Mission States
- `BriefingState` - Mission briefing
- `BriefingLightState` - Light mission briefing
- `DebriefingState` - Mission debriefing
- `AbortMissionState` - Mission abort state
- `ConfirmEndMissionState` - Mission end confirmation
- `AliensCrashState` - Alien crash site state
- `CannotReequipState` - Equipment reequipping issues

### Turn Management
- `NextTurnState` - Next turn management
- `TurnDiaryState` - Turn diary
- `InfoboxState` - Information box
- `InfoboxOKState` - Information box with OK button

### Unit Information
- `UnitInfoState` - Unit information display
- `SkillMenuState` - Skill menu
- `CommendationState` - Commendation system
- `CommendationLateState` - Late commendation
- `PromotionsState` - Promotions system
- `NoExperienceState` - No experience state
- `ExperienceOverviewState` - Experience overview

### UI Components
- `MiniMapView` - Mini-map view
- `MiniMapState` - Mini-map state
- `WarningMessage` - Warning message system

### Extended Systems
- `ExtendedBattlescapeLinksState` - Extended battlescape links
- `ExtendedInventoryLinksState` - Extended inventory links


## Engine Module

The Engine module provides the core infrastructure and utilities for the game, including rendering, audio, input handling, and game state management. Key components include:

### Core Game Systems
- `Game` - Main game engine and core functionality
- `State` - Game state management system
- `Action` - Action system for game events
- `Timer` - Timer and timing utilities
- `Options` - Game options and settings
- `ModInfo` - Mod information management

### Rendering and Graphics
- `Screen` - Screen management and rendering
- `Surface` - Surface rendering system
- `SurfaceSet` - Surface set management
- `OpenGL` - OpenGL rendering support
- `ShaderDraw` - Shader drawing system
- `ShaderMove` - Shader movement system
- `ShaderRepeat` - Shader repeat system
- `ShaderDrawHelper` - Shader drawing helper
- `InteractiveSurface` - Interactive surface system
- `TouchState` - Touch input state
- `FastLineClip` - Fast line clipping algorithm

### Audio and Music
- `Sound` - Sound system
- `SoundSet` - Sound set management
- `Music` - Music system
- `AdlibMusic` - Adlib music support
- `Adlib` - Adlib audio system
    - `fmopl` - FM OPL emulator
    - `adlplayer` - Adlib player

### Text and Fonts
- `Font` - Font system
- `DosFont` - DOS font support
- `Unicode` - Unicode support
- `Language` - Language system
- `LocalizedText` - Localized text system
- `LanguagePlurality` - Language plurality support

### File and Resource Management
- `CatFile` - CAT file handling
- `FileMap` - File mapping system
- `GMCat` - Game CAT file handling
- `Palette` - Color palette system

### Scripting and Modding
- `Script` - Script system
- `ScriptBind` - Script binding system
- `Yaml` - YAML support
- `HelperMeta` - Helper metadata

### Input and Controls
- `TouchState` - Touch input state
- `CrossPlatform` - Cross-platform input handling

### Scaling and Image Processing
- `Scalers` - Image scaling algorithms
    - `hqx` - HQX scaling algorithms (hq2x, hq3x, hq4x)
    - `xbrz` - XBRZ scaling algorithm
    - `scale2x` - Scale2x algorithm
    - `scale3x` - Scale3x algorithm
    - `scalebit` - Scale bit operations
    - `common` - Common scaling utilities
    - `config` - Scaling configuration
    - `init` - Scaling initialization

### Utilities and Helpers
- `Logger` - Logging system
- `Exception` - Exception handling
- `Collections` - Collection utilities
- `GraphSubset` - Graph subset utilities
- `Functions` - Function utilities
- `OptionInfo` - Option information
- `NullableValue` - Nullable value support
- `LocalizedText` - Localized text utilities

### Platform Support
- `CrossPlatform` - Cross-platform utilities
- `SDL2Helpers` - SDL2 helper functions


## Geoscape Module

The Geoscape module handles the global view, world map, UFO tracking, base management, and various global events. Key components include:

### Core Geoscape Systems
- `GeoscapeState` - Main geoscape state and game loop
- `Globe` - Globe/world map rendering and interaction
- `GeoscapeCraftState` - Craft management on the geoscape
- `GeoscapeEventState` - Event handling system
- `ExtendedGeoscapeLinksState` - Extended geoscape links

### UFO and Alien Activity
- `UfoTrackerState` - UFO tracking system
- `UfoDetectedState` - UFO detection notification
- `UfoLostState` - UFO lost notification
- `AlienBaseState` - Alien base detection and management
- `DogfightState` - Dogfight combat system
- `DogfightErrorState` - Dogfight error handling

### Base Management
- `BaseNameState` - Base naming functionality
- `BuildNewBaseState` - Building new bases
- `ConfirmNewBaseState` - New base confirmation
- `BaseDestroyedState` - Base destruction notification
- `BaseDefenseState` - Base defense scenarios

### Craft Management
- `CraftPatrolState` - Craft patrol management
- `CraftErrorState` - Craft error handling
- `CraftNotEnoughPilotsState` - Pilot shortage notification
- `InterceptState` - Craft interception system
- `LowFuelState` - Low fuel warning
- `SelectDestinationState` - Destination selection
- `ConfirmDestinationState` - Destination confirmation

### Research and Production
- `ResearchCompleteState` - Research completion notification
- `ResearchRequiredState` - Research requirement notification
- `ProductionCompleteState` - Production completion notification
- `NewPossibleResearchState` - New research opportunity
- `NewPossibleManufactureState` - New manufacturing opportunity
- `NewPossibleFacilityState` - New facility opportunity
- `NewPossiblePurchaseState` - New purchase opportunity

### Training Systems
- `TrainingState` - Main training system
- `AllocateTrainingState` - Training allocation
- `TrainingFinishedState` - Training completion
- `PsiTrainingState` - Psionic training
- `AllocatePsiTrainingState` - Psionic training allocation

### Event Management
- `GeoscapeEventState` - Event handling
- `MonthlyReportState` - Monthly report generation
- `GraphsState` - Statistics and graphs display
- `ItemsArrivingState` - Item arrival notification

### Mission Management
- `MissionDetectedState` - Mission detection
- `MultipleTargetsState` - Multiple target handling
- `SelectMusicTrackState` - Music track selection
- `ConfirmLandingState` - Landing confirmation
- `ConfirmCydoniaState` - Cydonia mission confirmation

### Funding and Economics
- `FundingState` - Funding management
- `MonthlyCostsState` - Monthly cost calculations

### Information and Reports
- `TargetInfoState` - Target information display
- `FundingState` - Funding information
- `AllocateTrainingState` - Training allocation interface

### Error Handling
- `CraftErrorState` - Craft error notifications
- `DogfightErrorState` - Dogfight error handling
- `UfoLostState` - UFO lost notifications
- `LowFuelState` - Fuel warning system

### Utility States
- `GeoscapeCraftState` - Craft overview
- `GeoscapeEventState` - Event notifications
- `ExtendedGeoscapeLinksState` - Extended functionality links


## Interface Module

The Interface module contains all the reusable UI components and widgets used throughout the game. These components provide the building blocks for creating user interfaces in both the geoscape and battlescape modes. Key components include:

### Basic UI Elements
- `Window` - Main container for UI elements with borders and title
- `Frame` - Decorative frame element for UI containers
- `Text` - Text rendering and display component
- `Bar` - Progress bar or status bar display
- `NumberText` - Numeric text display with formatting

### Input Controls
- `Slider` - Horizontal slider control for value selection
- `ComboBox` - Dropdown selection box with list of options
- `TextEdit` - Text input field for user entry
- `TextList` - Scrollable list of text items
- `ScrollBar` - Vertical scrollbar for scrolling content
- `Cursor` - Mouse cursor representation and handling

### Button Components
- `TextButton` - Button with text label
- `ArrowButton` - Button with arrow indicators (up/down/left/right)
- `ImageButton` - Button with image/icon display
- `ToggleTextButton` - Button that toggles between states (on/off)
- `BattlescapeButton` - Specialized button for battlescape interface

### Status Indicators
- `ProgressBar` - Progress bar for showing completion status
- `FpsCounter` - Frames per second counter for performance monitoring

### Container and Layout
- `Window` - Main container with title bar and borders
- `Frame` - Decorative frame that can contain other elements
- `TextList` - Container for displaying scrollable lists of text
- `ScrollBar` - Companion component for scrolling lists

### Specialized Components
- `BattlescapeButton` - Buttons specifically designed for battlescape UI
- `ToggleTextButton` - Toggle switches for options settings

### UI Interaction Features
- `TextButton` - Clickable text buttons with hover effects
- `ArrowButton` - Directional controls for scrolling and navigation
- `ImageButton` - Icon-based buttons with visual feedback
- `Slider` - Interactive sliders for adjusting values
- `ComboBox` - Dropdown menus with selection lists
- `TextEdit` - Editable text fields with keyboard input

### Visual Elements
- `Bar` - Horizontal bars for status indicators
- `ProgressBar` - Extended progress bars for longer operations
- `NumberText` - Formatted numeric display
- `Text` - Text rendering with different fonts and colors

### User Experience Components
- `Cursor` - Visual feedback for mouse interaction
- `FpsCounter` - Performance monitoring display
- `ScrollBar` - Navigation controls for large content areas

### Integration Features
- All interface components can be combined to create complex UI layouts
- Components are designed to work with both geoscape and battlescape modes
- Support for mouse, keyboard, and touch input where appropriate
- Customizable appearance through theme and style systems


## Menu Module

The Menu module handles all menu screens, game states, and user interface for the game's menus and configuration. This module provides the complete menu system including main menu, options, game management, and various utility screens. Key components include:

### Main Menu and Game States
- `MainMenuState` - Main menu screen with game options
- `StartState` - Game start screen
- `PauseState` - Pause menu during gameplay
- `NewGameState` - New game creation screen
- `LoadGameState` - Game loading screen
- `SaveGameState` - Game saving screen
- `ListLoadState` - List of saved games to load
- `ListSaveState` - List of save slots
- `ListGamesState` - Game selection screen
- `DeleteGameState` - Game deletion screen
- `AbandonGameState` - Game abandonment confirmation
- `ConfirmLoadState` - Load game confirmation
- `TestState` - Testing/debugging state

### Cutscenes and Visual Content
- `CutsceneState` - Cutscene playback system
- `SlideshowState` - Slideshow presentation state
- `TestPaletteState` - Palette testing screen

### Battle and Mission States
- `NewBattleState` - New battle/mission creation
- `NotesState` - Game notes/journal screen

### Mod Management
- `ModListState` - Mod selection and management
- `ModConfirmExtendedState` - Extended mod confirmation

### Options and Configuration
- `OptionsBaseState` - Base options state
- `OptionsAudioState` - Audio options configuration
- `OptionsVideoState` - Video/graphics options
- `OptionsControlsState` - Input controls configuration
- `OptionsGeoscapeState` - Geoscape-specific options
- `OptionsBattlescapeState` - Battlescape-specific options
- `OptionsAdvancedState` - Advanced game settings
- `OptionsFoldersState` - Folder/path configuration
- `OptionsDefaultsState` - Default settings restoration
- `OptionsConfirmState` - Options confirmation
- `OptionsNoAudioState` - No audio mode configuration

### Video and Display
- `VideoState` - Video mode and display settings
- `SetWindowedRootState` - Windowed mode configuration

### Game Management
- `StatisticsState` - Game statistics display
- `ErrorMessageState` - Error message display
- `ListLoadOriginalState` - Original game load list

### State Management System
- All menu states inherit from a common base state system
- State transitions and navigation between different screens
- Event handling for user input and menu interactions
- Save/load state persistence across menu screens

### User Interface Features
- Interactive menu navigation with keyboard and mouse
- Confirmation dialogs for important actions
- List-based interfaces for selection screens
- Configuration wizards for complex options
- Error handling and user feedback systems

### Integration Features
- Seamless integration with the main game state system
- Support for mod management and customization
- Configuration persistence across game sessions
- Accessibility features for different user preferences

### Specialized Features
- Cutscene system for narrative content
- Palette testing for visual debugging
- Statistics tracking and display
- Mod management for game customization
- Battle creation for testing scenarios



## Mod Module

The Mod module contains C++ source files that appear to be related to modular game content and rules.

### Core Mod Files:
- `Mod` - Main module file
- `MCDPatch` - MCD (Map Data) patching functionality

### Alien and Race Related:
- `AlienRace` - Alien race definitions
- `AlienDeployment` - Alien deployment logic
- `UfoTrajectory` - UFO movement patterns

### Map and Terrain:
- `MapScript` - Map scripting functionality
- `MapDataSet` - Map dataset management
- `MapData` - Core map data structures
- `MapBlock` - Map block definitions
- `Polyline` - Polyline geometry
- `Polygon` - Polygon geometry
- `RuleTerrain` - Terrain rules

### Rules and Game Systems:
- `RuleAlienMission` - Alien mission rules
- `RuleBaseFacility` - Base facility rules
- `RuleArcScript` - Arcade script rules
- `RuleCountry` - Country rules
- `RuleCraft` - Craft/vehicle rules
- `RuleConverter` - Data conversion rules
- `RuleCommendations` - Commendation system
- `RuleEvent` - Event rules
- `RuleEventScript` - Event scripting
- `RuleEnviroEffects` - Environmental effects
- `RuleGlobe` - Globe/world map rules
- `RuleInterface` - Interface rules
- `RuleItem` - Item rules
- `RuleItemCategory` - Item categorization
- `RuleInventory` - Inventory management
- `RuleDamageType` - Damage type definitions
- `RuleManufacture` - Manufacturing rules
- `RuleManufactureShortcut` - Manufacturing shortcuts
- `RuleMissionScript` - Mission scripting
- `RuleMusic` - Music system
- `Region` - Region definitions
- `Research` - Research system
- `RuleResearch` - Research rules
- `RuleSoldier` - Soldier rules
- `RuleSoldierBonus` - Soldier bonuses
- `RuleSoldierTransformation` - Soldier transformations
- `RuleSkill` - Skill system
- `RuleStartingCondition` - Starting conditions
- `RuleStatBonus` - Stat bonuses
- `RuleUfo` - UFO rules
- `RuleVideo` - Video/multimedia rules
- `RuleCraftWeapon` - Craft weapon systems
- `RuleWeaponSet` - Weapon set definitions

### Game Content Assets:
- `ExtraStrings` - Additional string resources
- `ExtraSprites` - Additional sprite resources
- `ExtraSounds` - Additional sound resources
- `CustomPalettes` - Custom color palettes
- `Texture` - Texture management
- `SoundDefinition` - Sound definition system

### Character and Unit Systems:
- `Unit` - Unit definitions
- `Armor` - Armor system
- `SoldierNamePool` - Soldier name generation

### UI and Interface Elements:
- `ArticleDefinition` - Article/encyclopedia definitions
- `City` - City management
- `StatString` - Stat string system
- `StatStringCondition` - Stat string conditions

### Architecture Notes:
- The Mod directory appears to handle game content, rules, and modular systems
- Heavy use of "Rule" prefixes suggests a rule-based game design system
- Files are well-organized by system (aliens, terrain, items, soldiers, etc.)
- Supports extensive customization through scripts and rules
- Contains asset management systems for sprites, sounds, and strings

## Savegame Module
The Savegame module handles all persistent game state management including player bases, soldiers, crafts, UFOs, missions, research, manufacturing, and battle data. It manages serialization/deserialization of game state to/from YAML format and tracks all dynamic game entities throughout both Geoscape and Battlescape operations.

### Core Game State
- `SavedGame` - Main save game state containing all player progress, bases, resources, and world activities
- `GameTime` - Tracks game clock and time progression
- `SaveConverter` - Handles save format conversions

### Base Management
- `Base` - Player base representation with facilities, personnel, and resources
- `BaseFacility` - Individual base facility with construction/upgrade states
- `BaseFacilityFunctions` - Facility functionality enumeration (quantities of quarters, labs, workshops, etc.)

### Personnel Management
- `Soldier` - Individual soldier with stats, rank, equipment, and career history
- `SoldierDeath` - Records soldier death information
- `SoldierDiary` - Tracks soldier's mission history and statistics
- `ResearchDiary` - Records research progress and discoveries
- `SoldierAvatar` - Handles soldier appearance/visual representation

### Military Assets
- `Craft` - Player-owned aircraft with weapons, fuel, damage, and crew assignments
- `CraftWeapon` - Craft-mounted weaponry
- `CraftWeaponProjectile` - Projectile mechanics for craft weapons
- `Vehicle` - Ground vehicles stored in bases or loaded onto crafts
- `Transfer` - Personnel/item transfers between bases

### Strategic Entities
- `Ufo` - Alien UFO tracking and interception
- `AlienBase` - Alien base on the geoscape
- `AlienMission` - Active alien missions
- `AlienStrategy` - Strategic alien behavior management
- `AlienRace` - Alien race types

### Geoscape Activities
- `MissionSite` - Geoscape mission locations
- `Waypoint` - Navigation points
- `GeoscapeEvent` - Random geoscape events
- `MovingTarget` - Base class for movable geoscape entities

### Research & Manufacturing
- `ResearchProject` - Research queue items and progress
- `Production` - Manufacturing queue items and progress
- `ResearchDiaryEntry` - Individual research diary records

### Battle System
- `SavedBattleGame` - Battle state container (Battlescape)
- `BattleUnit` - Units in battle (soldiers, aliens)
- `BattleItem` - Items in battle
- `BattleUnitStatistics` - Battle-specific statistics
- `HitLog` - Damage logging

### Economy & Resources
- `ItemContainer` - Inventory management (base, craft, battle)
- `EquipmentLayoutItem` - Equipment configuration templates
- `Production` - Manufacturing tracking
- `Transfer` - Base-to-base resource/personnel transfers

### Meta-Game Systems
- `RankCount` - Rank distribution tracking
- `WeightedOptions` - Weighted random selection utilities
- `SerializationHelper` - YAML serialization utilities

### Game Configuration
- `GameTime` - Time management and progression
- `GameDifficulty` - Difficulty setting enumeration
- `SaveType` - Save type classification (quick, auto, ironman, etc.)

### Utility & Statistics
- `MissionStatistics` - Battle mission statistics
- `BattleUnitKills` - Individual kill tracking
- `MissionStatistics` - Mission completion data
- `ItemContainer` - Inventory capacity and item tracking

### Script Integration (see `src/Engine/Script`)
- `Script` integration throughout for moddability
- `ScriptValues` - Dynamic script data attachment


## StreamerConsole Module
The StreamerConsole module provides integration with an external streaming console application, enabling real-time communication between the game and external tools through named pipes on Windows. It handles event processing, status management, and notification display for streamers.

### Core Communication
- `StreamerConsoleConnector` - Windows named pipe communication handler for bidirectional data exchange
- `EventsList` - Event processing system that parses YAML events and routes them to appropriate handlers

### Status Management
- `StatusManager` - Singleton manager for tracking active game events and their durations
- `Status` - Base class for event status tracking with YAML data storage
- `TimeBasedStatus` - Time-duration based event tracking with elapsed time calculation
- `CounterBasedStatus` - Counter-based event tracking for action-dependent events

### UI Components
- `NotificationMessage` - On-screen notification display with auto-hide timer (5 seconds)

### Rule Files (`src/StreamerConsole/rules/*.rul`)
- `custom_event_try.rul` - Custom event trigger rules
- `reinforcement_*.rul` - Reinforcement event rules for various factions (XCOM, alien, civilian) and difficulty levels


## Ufopaedia Module

The Ufopaedia module provides an in-game encyclopedia system that displays researched content including weapon specifications, alien lifeforms, base facilities, vehicles, and technology information. The module manages article navigation, visibility based on research progress, and integrates with the Stats for Nerds feature for detailed technical information.

### Core Interface
- `Ufopaedia` - Static class managing Ufopaedia operations including article opening, navigation, and visibility checks
- `ArticleCommonState` - Shared state structure for article navigation and pagination
- `ArticleState` - Base class for all article states with common UI elements and navigation controls

### Start and Selection
- `UfopaediaStartState` - Main entry screen presenting section selection buttons with scrolling navigation
- `UfopaediaSelectState` - Article listing screen for specific categories with search and filtering capabilities


### Article Display States
#### Base Game Articles
- `ArticleStateItem` - Detailed weapon and equipment specifications
- `ArticleStateArmor` - Soldier armor and protection statistics
- `ArticleStateCraft` - Aircraft and transport craft specifications
- `ArticleStateCraftWeapon` - Craft weapon systems and ammunition
- `ArticleStateVehicle` - Ground vehicle technical specifications
- `ArticleStateSoldier` - Soldier recruitment and capability information
- `ArticleStateBaseFacility` - Base construction and facility details
- `ArticleStateUnit` - Alien lifeform combat statistics
- `ArticleStateUfo` - UFO specifications and capabilities
- `ArticleStateText` - Text-only articles for descriptive content
- `ArticleStateTextImage` - Articles combining text with graphical content

#### TFTD (Terror From The Deep) Articles
- `ArticleStateTFTD` - Base class for TFTD-specific article types
- `ArticleStateTFTDArmor` - Underwater armor specifications
- `ArticleStateTFTDCraft` - Aquatic craft and submersible details
- `ArticleStateTFTDCraftWeapon` - Underwater craft weapon systems
- `ArticleStateTFTDItem` - Underwater equipment and weapons
- `ArticleStateTFTDFacility` - Aquatic base facility information
- `ArticleStateTFTDVehicle` - Underwater vehicle specifications
- `ArticleStateTFTDUso` - USO (Unidentified Submersible Object) details

### Advanced Features
- `StatsForNerdsState` - Detailed technical data viewer showing raw ruleset values with filtering options for debug info, IDs, and default values