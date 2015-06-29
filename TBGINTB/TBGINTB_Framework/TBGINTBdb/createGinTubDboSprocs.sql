USE [GinTub]

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
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
	FROM [dbo].[Rooms] r
	INNER JOIN [dbo].[Players] p
	ON p.[Id] = @player
	
	INSERT INTO [dbo].[PlayerStatesOfParagraphs] ([Player], [Paragraph], [State], [CheckpointDate])
	SELECT @player,
		   para.[Id],
		   0,
		   p.[LastCheckpoint]
	FROM [dbo].[Paragraphs] para
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
	FROM [dbo].[Nouns] n
	INNER JOIN [dbo].[ParagraphStates] ps
	ON n.[ParagraphState] = ps.[Id]
	INNER JOIN [dbo].[PlayerStatesOfParagraphs] psp
	ON ps.[Paragraph] = psp.[Paragraph] AND ps.[State] = psp.[State]
	INNER JOIN [dbo].[Paragraphs] p
	ON ps.[Paragraph] = p.[Id]
	INNER JOIN [dbo].[RoomStates] rs
	ON p.[RoomState] = rs.[Id] OR p.[RoomState] IS NULL
	INNER JOIN [dbo].[PlayerStatesOfRooms] psr
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
	FROM [dbo].[ParagraphStates] ps
	INNER JOIN [dbo].[PlayerStatesOfParagraphs] psp
	ON ps.[Paragraph] = psp.[Paragraph] AND ps.[State] = psp.[State]
	INNER JOIN [dbo].[Paragraphs] p
	ON ps.[Paragraph] = p.[Id]
	INNER JOIN [dbo].[RoomStates] rs
	ON p.[RoomState] = rs.[Id] OR p.[RoomState] IS NULL
	INNER JOIN [dbo].[PlayerStatesOfRooms] psr
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
	FROM [dbo].[RoomStates] rs
	INNER JOIN [dbo].[Locations] l
	ON rs.[Location] = l.[Id]
	INNER JOIN [dbo].[PlayerStatesOfRooms] psr
	ON rs.[Room] = psr.[Room] AND rs.[State] = psr.[State]
	WHERE rs.[Room] = @room
	AND psr.[Player] = @player

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dbo].[LoadRoom]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
  EXEC('CREATE PROCEDURE [dbo].[LoadRoom] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/26/2015
-- Description:	Loads room data for a player
-- =============================================
ALTER PROCEDURE [dbo].[LoadRoom]
	@player uniqueidentifier,
	@area int,
	@x int,
	@y int,
	@z int
AS
BEGIN

	DECLARE @room int
	SELECT @room = [Id]
	FROM [dbo].[Rooms]
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

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dbo].[LoadNewGame]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
  EXEC('CREATE PROCEDURE [dbo].[LoadNewGame] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/26/2015
-- Description:	Loads data for a new game
-- =============================================
ALTER PROCEDURE [dbo].[LoadNewGame]
	@player uniqueidentifier
AS
BEGIN

	DECLARE @area int
	DECLARE @x int
	DECLARE @y int
	DECLARE @z int
	SELECT @area = aril.[Area],
		   @x = r.[X],
		   @y = r.[Y],
		   @z = r.[Z]
	FROM [dbo].[AreaRoomOnInitialLoad] aril
	INNER JOIN [dbo].[Rooms] r
	ON aril.[Room] = r.[Id]
	
	EXEC [dbo].[LoadRoom]
	@player = @player,
	@area = @area,
	@x = @x,
	@y = @y,
	@z = @z

END
GO