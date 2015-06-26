USE [GinTub]

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dbo].[dbo_LoadDefaultPlayerStates]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
  EXEC('CREATE PROCEDURE [dbo].[dbo_LoadDefaultPlayerStates] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/26/2015
-- Description:	
-- =============================================
ALTER PROCEDURE [dbo].[dbo_LoadDefaultPlayerStates]
	@playerId uniqueidentifier
AS
BEGIN

	INSERT INTO [dbo].[PlayerStatesOfRooms] ([Player], [Room], [State], [CheckpointDate])
	SELECT @playerId,
		   r.[Id],
		   0,
		   p.[LastCheckpoint]
	FROM [dbo].[Rooms] r
	INNER JOIN [dbo].[Players] p
	ON p.[Id] = @playerId
	
	INSERT INTO [dbo].[PlayerStatesOfParagraphs] ([Player], [Paragraph], [State], [CheckpointDate])
	SELECT @playerId,
		   para.[Id],
		   0,
		   p.[LastCheckpoint]
	FROM [dbo].[Paragraphs] para
	INNER JOIN [dbo].[Players] p
	ON p.[Id] = @playerId

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dbo].[dbo_LoadRoom]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
  EXEC('CREATE PROCEDURE [dbo].[dbo_LoadRoom] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/26/2015
-- Description:	Loads room data for a player
-- =============================================
ALTER PROCEDURE [dbo].[dbo_LoadRoom]
	@playerId uniqueidentifier,
	@area int,
	@x int,
	@y int,
	@z int
AS
BEGIN

	DECLARE @roomId int
	SELECT @roomId = [Id]
	FROM [dbo].[Rooms]
	WHERE [Area] = @area
	AND [X] = @x
	AND [Y] = @y
	AND [Z] = @z
	
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
	WHERE rs.[Room] = @roomId
	AND psr.[Player] = @playerId
	
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
	WHERE p.[Room] = @roomId
	AND rs.[Room] = @roomId
	
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
	WHERE p.[Room] = @roomId
	AND rs.[Room] = @roomId

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dbo].[dbo_LoadNewGame]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
  EXEC('CREATE PROCEDURE [dbo].[dbo_LoadNewGame] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/26/2015
-- Description:	Loads data for a new game
-- =============================================
ALTER PROCEDURE [dbo].[dbo_LoadNewGame]
	@playerId uniqueidentifier
AS
BEGIN

	SELECT 1

END
GO