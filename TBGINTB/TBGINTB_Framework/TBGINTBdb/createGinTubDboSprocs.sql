USE [GinTub]

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO


IF NOT EXISTS (SELECT * FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dbo].[f_PlayerHasRequirementsForAction]') AND [xtype] = 'FN')
  EXEC('CREATE FUNCTION [dbo].[f_PlayerHasRequirementsForAction] () RETURNS bit AS BEGIN RETURN 1 END')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/30/2015
-- Description:	Verifies that the specified Player has all the appropriate Requirements to
-- perform an Action
-- =============================================
ALTER FUNCTION [dbo].[f_PlayerHasRequirementsForAction]
(
	@player uniqueidentifier,
	@action int
)
RETURNS bit
AS
BEGIN
	DECLARE @result1 bit, @result2 bit, @result3 bit

	SELECT @result1 = CASE COUNT(*) WHEN 0 THEN 1 ELSE 0 END
	FROM [dbo].[ItemActionRequirements] iar WITH (NOLOCK)
	INNER JOIN [dbo].[PlayerInventory] pli WITH (NOLOCK)
	ON iar.[Item] = pli.[Item] AND pli.[Player] = @player
	WHERE iar.[Action] = @action
	AND pli.[InInventory] = 0
	
	SELECT @result2 = CASE COUNT(*) WHEN 0 THEN 1 ELSE 0 END
	FROM [dbo].[EventActionRequirements] ear WITH (NOLOCK)
	INNER JOIN [dbo].[PlayerHistory] pli WITH (NOLOCK)
	ON ear.[Event] = pli.[Event] AND pli.[Player] = @player
	WHERE ear.[Action] = @action
	AND pli.[InHistory] = 0

	SELECT @result3 = CASE COUNT(*) WHEN 0 THEN 1 ELSE 0 END
	FROM [dbo].[CharacterActionRequirements] car  WITH (NOLOCK)
	INNER JOIN [dbo].[PlayerParty] pli WITH (NOLOCK)
	ON car.[Character] = pli.[Character] AND pli.[Player] = @player
	WHERE car.[Action] = @action
	AND pli.[InParty] = 0

	RETURN @result1 & @result2 & @result3

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dbo].[CreateDefaultPlayerStates]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
  EXEC('CREATE PROCEDURE [dbo].[CreateDefaultPlayerStates] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/26/2015
-- Description:	Enters records into the PlayerStatesOfRooms and PlayersStatesOfParagraphs
-- table upon initial load
-- =============================================
ALTER PROCEDURE [dbo].[CreateDefaultPlayerStates]
	@player uniqueidentifier
AS
BEGIN

	INSERT INTO [dbo].[PlayerStatesOfRooms] ([Player], [Room], [State], [CheckpointDate])
	SELECT @player,
		   r.[Id],
		   0,
		   p.[LastCheckpoint]
	FROM [dbo].[Rooms] r WITH (NOLOCK)
	INNER JOIN [dbo].[Players] p
	ON p.[Id] = @player
	
	INSERT INTO [dbo].[PlayerStatesOfParagraphs] ([Player], [Paragraph], [State], [CheckpointDate])
	SELECT @player,
		   para.[Id],
		   0,
		   p.[LastCheckpoint]
	FROM [dbo].[Paragraphs] para WITH (NOLOCK)
	INNER JOIN [dbo].[Players] p
	ON p.[Id] = @player

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dbo].[CreateDefaultPlayerInventories]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
  EXEC('CREATE PROCEDURE [dbo].[CreateDefaultPlayerInventories] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/30/2015
-- Description:	Enters records into the PlayerInventory, PlayerHistory, and PlayerParty tables upon load
-- =============================================
ALTER PROCEDURE [dbo].[CreateDefaultPlayerInventories]
	@player uniqueidentifier
AS
BEGIN

	INSERT INTO [dbo].[PlayerInventory] ([Player], [Item], [InInventory], [CheckpointDate])
	SELECT @player,
		   x.[Id],
		   0,
		   p.[LastCheckpoint]
	FROM [dbo].[Items] x WITH (NOLOCK)
	INNER JOIN [dbo].[Players] p
	ON p.[Id] = @player

	INSERT INTO [dbo].[PlayerHistory] ([Player], [Event], [InHistory], [CheckpointDate])
	SELECT @player,
		   x.[Id],
		   0,
		   p.[LastCheckpoint]
	FROM [dbo].[Events] x WITH (NOLOCK)
	INNER JOIN [dbo].[Players] p
	ON p.[Id] = @player

	INSERT INTO [dbo].[PlayerParty] ([Player], [Character], [InParty], [CheckpointDate])
	SELECT @player,
		   x.[Id],
		   0,
		   p.[LastCheckpoint]
	FROM [dbo].[Character] x WITH (NOLOCK)
	INNER JOIN [dbo].[Players] p
	ON p.[Id] = @player

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dbo].[LoadNounsForRoom]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
  EXEC('CREATE PROCEDURE [dbo].[LoadNounsForRoom] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/28/2015
-- Description:	Loads all Noun data for a Room and Player
-- =============================================
ALTER PROCEDURE [dbo].[LoadNounsForRoom]
	@player uniqueidentifier,
	@room int
AS
BEGIN

	SELECT n.[Id],
		   n.[Text],
		   n.[ParagraphState]
	FROM [dbo].[Nouns] n WITH (NOLOCK)
	INNER JOIN [dbo].[ParagraphStates] ps WITH (NOLOCK)
	ON n.[ParagraphState] = ps.[Id]
	INNER JOIN [dbo].[PlayerStatesOfParagraphs] psp WITH (NOLOCK)
	ON ps.[Paragraph] = psp.[Paragraph] AND ps.[State] = psp.[State]
	INNER JOIN [dbo].[Paragraphs] p WITH (NOLOCK)
	ON ps.[Paragraph] = p.[Id]
	INNER JOIN [dbo].[RoomStates] rs WITH (NOLOCK)
	ON p.[RoomState] = rs.[Id] OR p.[RoomState] IS NULL
	INNER JOIN [dbo].[PlayerStatesOfRooms] psr WITH (NOLOCK)
	ON rs.[Room] = psr.[Room] AND rs.[State] = psr.[State]
	WHERE p.[Room] = @room
	AND rs.[Room] = @room
	AND psp.[Player] = @player
	AND psr.[Player] = @player

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dbo].[LoadParagraphStatesForRoom]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
  EXEC('CREATE PROCEDURE [dbo].[LoadParagraphStatesForRoom] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/28/2015
-- Description:	Loads all Paragraph data for a Room and Player
-- =============================================
ALTER PROCEDURE [dbo].[LoadParagraphStatesForRoom]
	@player uniqueidentifier,
	@room int
AS
BEGIN

	SELECT ps.[Id],
		   ps.[Text],
		   p.[Order],
		   p.[RoomState]
	FROM [dbo].[ParagraphStates] ps WITH (NOLOCK)
	INNER JOIN [dbo].[PlayerStatesOfParagraphs] psp WITH (NOLOCK)
	ON ps.[Paragraph] = psp.[Paragraph] AND ps.[State] = psp.[State]
	INNER JOIN [dbo].[Paragraphs] p WITH (NOLOCK)
	ON ps.[Paragraph] = p.[Id]
	INNER JOIN [dbo].[RoomStates] rs WITH (NOLOCK)
	ON p.[RoomState] = rs.[Id] OR p.[RoomState] IS NULL
	INNER JOIN [dbo].[PlayerStatesOfRooms] psr WITH (NOLOCK)
	ON rs.[Room] = psr.[Room] AND rs.[State] = psr.[State]
	WHERE p.[Room] = @room
	AND rs.[Room] = @room
	AND psp.[Player] = @player
	AND psr.[Player] = @player

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dbo].[LoadRoomStatesForRoom]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
  EXEC('CREATE PROCEDURE [dbo].[LoadRoomStatesForRoom] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/26/2015
-- Description:	Loads room data for a player
-- =============================================
ALTER PROCEDURE [dbo].[LoadRoomStatesForRoom]
	@player uniqueidentifier,
	@room int
AS
BEGIN

	SELECT rs.[Id],
		   rs.[State],
		   rs.[Time],
		   l.[LocationFile] AS [Location],
		   rs.[Room]
	FROM [dbo].[RoomStates] rs WITH (NOLOCK)
	INNER JOIN [dbo].[Locations] l WITH (NOLOCK)
	ON rs.[Location] = l.[Id]
	INNER JOIN [dbo].[PlayerStatesOfRooms] psr WITH (NOLOCK)
	ON rs.[Room] = psr.[Room] AND rs.[State] = psr.[State]
	WHERE rs.[Room] = @room
	AND psr.[Player] = @player

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dbo].[LoadRoomXYZ]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
  EXEC('CREATE PROCEDURE [dbo].[LoadRoomXYZ] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/26/2015
-- Description:	Loads room data for a player
-- =============================================
ALTER PROCEDURE [dbo].[LoadRoomXYZ]
	@player uniqueidentifier,
	@area int,
	@x int,
	@y int,
	@z int
AS
BEGIN

	DECLARE @room int
	SELECT @room = [Id]
	FROM [dbo].[Rooms] WITH (NOLOCK)
	WHERE [Area] = @area
	AND [X] = @x
	AND [Y] = @y
	AND [Z] = @z
	
	EXEC [dbo].[LoadRoomStatesForRoom]
	@player = @player,
	@room = @room
	
	EXEC [dbo].[LoadParagraphStatesForRoom]
	@player = @player,
	@room = @room
	
	EXEC [dbo].[LoadNounsForRoom]
	@player = @player,
	@room = @room

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dbo].[LoadRoomId]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
  EXEC('CREATE PROCEDURE [dbo].[LoadRoomId] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/26/2015
-- Description:	Loads room data for a player
-- =============================================
ALTER PROCEDURE [dbo].[LoadRoomId]
	@player uniqueidentifier,
	@room int
AS
BEGIN
	
	EXEC [dbo].[LoadRoomStatesForRoom]
	@player = @player,
	@room = @room
	
	EXEC [dbo].[LoadParagraphStatesForRoom]
	@player = @player,
	@room = @room
	
	EXEC [dbo].[LoadNounsForRoom]
	@player = @player,
	@room = @room

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dbo].[LoadArea]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
  EXEC('CREATE PROCEDURE [dbo].[LoadArea] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/29/2015
-- Description:	Loads Area data for a player
-- =============================================
ALTER PROCEDURE [dbo].[LoadArea]
	@area int
AS
BEGIN

	SELECT [Id],
		   [Name]
	FROM [dbo].[Areas] WITH (NOLOCK)
	WHERE [Id] = @area

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dbo].[LoadGame]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
  EXEC('CREATE PROCEDURE [dbo].[LoadGame] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/26/2015
-- Description:	Loads data for a new game
-- =============================================
ALTER PROCEDURE [dbo].[LoadGame]
	@player uniqueidentifier
AS
BEGIN

	DECLARE @area int
	DECLARE @x int
	DECLARE @y int
	DECLARE @z int
	SELECT @area = r.[Area],
		   @x = r.[X],
		   @y = r.[Y],
		   @z = r.[Z]
	FROM [dbo].[Players] p WITH (NOLOCK)
	INNER JOIN [dbo].[Rooms] r WITH (NOLOCK)
	ON p.[LastRoom] = r.[Id]
	
	EXEC [dbo].[LoadArea]
	@area = @area
	
	EXEC [dbo].[LoadRoomXYZ]
	@player = @player,
	@area = @area,
	@x = @x,
	@y = @y,
	@z = @z

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dbo].[GetActionResults]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
  EXEC('CREATE PROCEDURE [dbo].[GetActionResults] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/30/2015
-- Description:	Retrieves all Results for an Action, if the specified Player has the proper Requirements
-- =============================================
ALTER PROCEDURE [dbo].[GetActionResults]
	@player uniqueidentifier,
	@noun int,
	@verbType int
AS
BEGIN

	SELECT r.[Id],
		   r.[JSONData],
		   r.[ResultType]
	FROM [dbo].[Actions] a WITH (NOLOCK)
	INNER JOIN [dbo].[ActionResults] ar WITH (NOLOCK)
	ON a.[Id] = ar.[Action]
	INNER JOIN [dbo].[Results] r WITH (NOLOCK)
	ON ar.[Result] = r.[Id]
	WHERE a.[Noun] = @noun
	AND a.[VerbType] = @verbType
	AND [dbo].[f_PlayerHasRequirementsForAction](@player, a.[Id]) = 1

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dbo].[GetMessageChoiceResults]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
  EXEC('CREATE PROCEDURE [dbo].[GetMessageChoiceResults] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/30/2015
-- Description:	Retrieves all Results for an MessageChoice
-- =============================================
ALTER PROCEDURE [dbo].[GetMessageChoiceResults]
	@messageChoice int
AS
BEGIN

	SELECT r.[Id],
		   r.[JSONData],
		   r.[ResultType]
	FROM [dbo].[MessageChoiceResults] mr WITH (NOLOCK)
	INNER JOIN [dbo].[Results] r WITH (NOLOCK)
	ON mr.[Result] = r.[Id]
	WHERE mr.[MessageChoice] = @messageChoice

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dbo].[MovePlayerXYZ]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
  EXEC('CREATE PROCEDURE [dbo].[MovePlayerXYZ] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/30/2015
-- Description:	Loads Area data for a player
-- =============================================
ALTER PROCEDURE [dbo].[MovePlayerXYZ]
	@player uniqueidentifier,
	@area int,
	@xDir int,
	@yDir int,
	@zDir int
AS
BEGIN

	DECLARE @room int
	SELECT @room = r.[Id]
	FROM [dbo].[Rooms] r WITH (NOLOCK)
	INNER JOIN [dbo].[Players] p WITH (NOLOCK)
	ON p.[Id] = @player
	INNER JOIN [dbo].[Rooms] r2 WITH (NOLOCK)
	ON p.[LastRoom] = r2.[Id]
	WHERE r.[Area] = @area
	AND r.[X] = r2.[X] + @xDir
	AND r.[Y] = r2.[Y] + @yDir
	AND r.[Z] = r2.[Z] + @zDir
	
	UPDATE [dbo].[Players]
	SET [LastCheckpoint] = GETDATE(),
		[LastRoom] = @room
		
	EXEC [dbo].[LoadRoomId] 
	@player = @player, 
	@room = @room

END
GO