USE [GinTub]

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_ClearDatabase]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
  EXEC('CREATE PROCEDURE [dev].[dev_ClearDatabase] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/16/2015
-- Description:	Completely removes everything from the database
-- =============================================
ALTER PROCEDURE [dev].[dev_ClearDatabase]
	@backupfile varchar(MAX)
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;
	
	IF @backupfile IS NOT NULL AND @backupfile <> ''
	BEGIN
		BACKUP DATABASE [GinTub]
		TO DISK = @backupfile
	END

	EXEC [dev].[dev_DeleteAllItems]
	EXEC [dev].[dev_DeleteAllEvents]
	EXEC [dev].[dev_DeleteAllCharacters]
	EXEC [dev].[dev_DeleteAllResultTypes]
	EXEC [dev].[dev_DeleteAllVerbTypes]
	EXEC [dev].[dev_DeleteAllLocations]
	EXEC [dev].[dev_DeleteAllMessages]
	EXEC [dev].[dev_DeleteAllAreas]

END
GO

/******************************************************************************************************************************************/
/*Area*************************************************************************************************************************************/
/******************************************************************************************************************************************/

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_AddArea]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
  EXEC('CREATE PROCEDURE [dev].[dev_AddArea] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/12/2015
-- Description:	Adds an Area record and returns the newly generated ID
-- =============================================
ALTER PROCEDURE [dev].[dev_AddArea]
	@name varchar(500)
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	INSERT INTO [dbo].[Areas] ([Name])
	VALUES (@name)
	
	SELECT SCOPE_IDENTITY()

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_UpdateArea]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_UpdateArea] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/12/2015
-- Description:	Updates an Area record
-- =============================================
ALTER PROCEDURE [dev].[dev_UpdateArea]
	@id int,
	@name varchar(500)
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	UPDATE [dbo].[Areas]
	SET [Name] = @name
	WHERE [Id] = @id

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_GetAllAreas]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_GetAllAreas] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/14/2015
-- Description:	Gets the Id and Name fields of all Area records currently in the database
-- =============================================
ALTER PROCEDURE [dev].[dev_GetAllAreas]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [Id],
		   [Name]
	FROM [dbo].[Areas]

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_GetArea]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_GetArea] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/14/2015
-- Description:	Gets data about an Area record in the database
-- =============================================
ALTER PROCEDURE [dev].[dev_GetArea]
	@id int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT a.[Id],
		   a.[Name],
		   ISNULL(MAX(r.[X]), 0) AS [MaxX],
		   ISNULL(MIN(r.[X]), 0) AS [MinX],
		   ISNULL(MAX(r.[Y]), 0) AS [MaxY],
		   ISNULL(MIN(r.[Y]), 0) AS [MinY],
		   ISNULL(MAX(r.[Z]), 0) AS [MaxZ],
		   ISNULL(MIN(r.[Z]), 0) AS [MinZ],
		   COUNT(r.[Id]) AS [NumRooms]
	FROM [dbo].[Areas] a
	LEFT JOIN [dbo].[Rooms] r
	ON r.[Area] = a.[Id]
	WHERE a.[Id] = @id
	GROUP BY a.[Id], a.[Name]

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_DeleteAllAreas]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_DeleteAllAreas] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/15/2015
-- Description:	Deletes all Area records and resets the seed
-- =============================================
ALTER PROCEDURE [dev].[dev_DeleteAllAreas]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;
	
	DELETE
	FROM [dbo].[ItemActionRequirements]
	
	DELETE
	FROM [dbo].[EventActionRequirements]
	
	DELETE
	FROM [dbo].[CharacterActionRequirements]
	
	DELETE
	FROM [dbo].[ActionResults]
	
	DELETE
	FROM [dbo].[Actions]

	DELETE
	FROM [dbo].[Nouns]

	DELETE
	FROM [dbo].[ParagraphStates]

	DELETE
	FROM [dbo].[Paragraphs]

	DELETE
	FROM [dbo].[RoomStates]

	DELETE
	FROM [dbo].[Rooms]
	
	DELETE 
	FROM [dbo].[Areas]

	DBCC CHECKIDENT ('[dbo].[ItemActionRequirements]', RESEED, 0)
	DBCC CHECKIDENT ('[dbo].[EventActionRequirements]', RESEED, 0)
	DBCC CHECKIDENT ('[dbo].[CharacterActionRequirements]', RESEED, 0)
	DBCC CHECKIDENT ('[dbo].[ActionResults]', RESEED, 0)
	DBCC CHECKIDENT ('[dbo].[Actions]', RESEED, 0)
	DBCC CHECKIDENT ('[dbo].[Nouns]', RESEED, 0)
	DBCC CHECKIDENT ('[dbo].[ParagraphStates]', RESEED, 0)
	DBCC CHECKIDENT ('[dbo].[Paragraphs]', RESEED, 0)
	DBCC CHECKIDENT ('[dbo].[RoomStates]', RESEED, 0)
	DBCC CHECKIDENT ('[dbo].[Rooms]', RESEED, 0)
	DBCC CHECKIDENT ('[dbo].[Areas]', RESEED, 0)

END
GO

/******************************************************************************************************************************************/
/*Location*********************************************************************************************************************************/
/******************************************************************************************************************************************/

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_AddLocation]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_AddLocation] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/12/2015
-- Description:	Adds a Location record and returns the newly generated ID
-- =============================================
ALTER PROCEDURE [dev].[dev_AddLocation]
	@name varchar(500),
	@locationfile varchar(MAX)
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	INSERT INTO [dbo].[Locations] ([Name], [LocationFile])
	VALUES (@name, @locationfile)
	
	SELECT SCOPE_IDENTITY()

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_UpdateLocation]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_UpdateLocation] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/12/2015
-- Description:	Updates a Location record
-- =============================================
ALTER PROCEDURE [dev].[dev_UpdateLocation]
	@id int,
	@name varchar(500),
	@locationfile varchar(MAX)
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	UPDATE [dbo].[Locations] 
	SET	[Name] = ISNULL(@name, [Name]),
		[LocationFile] = ISNULL(@locationfile, [LocationFile])
	WHERE [Id] = @id

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_GetAllLocations]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_GetAllLocations] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/20/2015
-- Description:	Gets the Id and Location fields of all Location records currently in the database
-- =============================================
ALTER PROCEDURE [dev].[dev_GetAllLocations]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [Id],
		   [Name],
		   [LocationFile]
	FROM [dbo].[Locations]

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_GetLocation]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_GetLocation] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/20/2015
-- Description:	Gets data about an Location record in the database
-- =============================================
ALTER PROCEDURE [dev].[dev_GetLocation]
	@id int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [Id],
		   [Name],
		   [LocationFile]
	FROM [dbo].[Locations]
	WHERE [Id] = @id

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_DeleteAllLocations]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_DeleteAllLocations] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/16/2015
-- Description:	Deletes the Id and Location fields of all Location records currently in the database
-- =============================================
ALTER PROCEDURE [dev].[dev_DeleteAllLocations]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;
	
	DELETE
	FROM [dbo].[ItemActionRequirements]
	
	DELETE
	FROM [dbo].[EventActionRequirements]
	
	DELETE
	FROM [dbo].[CharacterActionRequirements]
	
	DELETE
	FROM [dbo].[ActionResults]
	
	DELETE
	FROM [dbo].[Actions]

	DELETE
	FROM [dbo].[Nouns]

	DELETE
	FROM [dbo].[ParagraphStates]

	DELETE
	FROM [dbo].[Paragraphs]
	WHERE [RoomState] IS NOT NULL

	DELETE
	FROM [dbo].[RoomStates]

	DELETE
	FROM [dbo].[Locations]
	
	DBCC CHECKIDENT ('[dbo].[ItemActionRequirements]', RESEED, 0)
	DBCC CHECKIDENT ('[dbo].[EventActionRequirements]', RESEED, 0)
	DBCC CHECKIDENT ('[dbo].[CharacterActionRequirements]', RESEED, 0)
	DBCC CHECKIDENT ('[dbo].[ActionResults]', RESEED, 0)
	DBCC CHECKIDENT ('[dbo].[Actions]', RESEED, 0)
	DBCC CHECKIDENT ('[dbo].[Nouns]', RESEED, 0)
	DBCC CHECKIDENT ('[dbo].[ParagraphStates]', RESEED, 0)
	DBCC CHECKIDENT ('[dbo].[RoomStates]', RESEED, 0)
	DBCC CHECKIDENT ('[dbo].[Locations]', RESEED, 0)

END
GO

/******************************************************************************************************************************************/
/*Room*************************************************************************************************************************************/
/******************************************************************************************************************************************/

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_AddRoom]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_AddRoom] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/12/2015
-- Description:	Adds a Room record and returns the newly generated ID
-- =============================================
ALTER PROCEDURE [dev].[dev_AddRoom]
	@name varchar(500),
	@x int,
	@y int,
	@z int,
	@area int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	INSERT INTO [dbo].[Rooms] ([Name], [X], [Y], [Z], [Area])
	VALUES (@name, @x, @y, @z, @area)
	
	SELECT SCOPE_IDENTITY()

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_UpdateRoom]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_UpdateRoom] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/12/2015
-- Description:	Updates a Room record
-- =============================================
ALTER PROCEDURE [dev].[dev_UpdateRoom]
	@id int,
	@name varchar(500),
	@x int,
	@y int,
	@z int,
	@area int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	UPDATE [dbo].[Rooms] 
	SET	[Name] = ISNULL(@name, [Name]), 
		[X] = ISNULL(@x, [X]),
		[Y] = ISNULL(@y, [Y]),
		[Z] = ISNULL(@z, [Z]),
		[Area] = ISNULL(@area, [Area])
	WHERE [Id] = @id

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_ShiftRoom]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_ShiftRoom] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/12/2015
-- Description:	Increments/decrements the specified Room record's X, Y, and Z values
-- =============================================
ALTER PROCEDURE [dev].[dev_ShiftRoom]
	@id int,
	@xIncr int,
	@yIncr int,
	@zIncr int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	UPDATE [dbo].[Rooms] 
	SET	[X] = [X] + @xIncr,
		[Y] = [Y] + @yIncr,
		[Z] = [Z] + @zIncr
	WHERE [Id] = @id

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_GetAllRoomsInArea]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_GetAllRoomsInArea] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/14/2015
-- Description:	Gets all Room records associated with the specified Area
-- =============================================
ALTER PROCEDURE [dev].[dev_GetAllRoomsInArea]
	@area int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [Id],
		   [Name],
		   [X],
		   [Y],
		   [Z],
		   [Area]
	FROM [dbo].[Rooms]
	WHERE [Area] = @area

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_GetAllRoomsInAreaOnFloor]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_GetAllRoomsInAreaOnFloor] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/19/2015
-- Description:	Gets all Room records associated with the specified Area, on a specific floor (Z)
-- =============================================
ALTER PROCEDURE [dev].[dev_GetAllRoomsInAreaOnFloor]
	@area int,
	@z int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [Id],
		   [Name],
		   [X],
		   [Y],
		   [Z],
		   [Area]
	FROM [dbo].[Rooms]
	WHERE [Area] = @area
	AND [Z] = @z

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_GetRoom]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_GetRoom] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/15/2015
-- Description:	Gets data about an Room record in the database
-- =============================================
ALTER PROCEDURE [dev].[dev_GetRoom]
	@id int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [Id],
		   [Name],
		   [X],
		   [Y],
		   [Z],
		   [Area]
	FROM [dbo].[Rooms]
	WHERE [Id] = @id

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_DeleteAllRoomsInArea]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_DeleteAllRoomsInArea] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/16/2015
-- Description:	Deletes all Room records associated with the specified Area
-- =============================================
ALTER PROCEDURE [dev].[dev_DeleteAllRoomsInArea]
	@area int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;
	
	DELETE ar
	FROM [dbo].[ItemActionRequirements] ar
	INNER JOIN [dbo].[Actions] a
	ON ar.[Action] = a.[Id]
	INNER JOIN [dbo].[Nouns] n
	ON a.[Noun] = n.[Id]
	INNER JOIN [dbo].[ParagraphStates] ps
	ON n.[ParagraphState] = ps.[Id]
	INNER JOIN [dbo].[Paragraphs] p
	ON ps.[Paragraph] = p.[Id]
	INNER JOIN [dbo].[Rooms] r
	ON p.[Room] = r.[Id]
	WHERE r.[Area] = @area
	
	DELETE ar
	FROM [dbo].[EventActionRequirements] ar
	INNER JOIN [dbo].[Actions] a
	ON ar.[Action] = a.[Id]
	INNER JOIN [dbo].[Nouns] n
	ON a.[Noun] = n.[Id]
	INNER JOIN [dbo].[ParagraphStates] ps
	ON n.[ParagraphState] = ps.[Id]
	INNER JOIN [dbo].[Paragraphs] p
	ON ps.[Paragraph] = p.[Id]
	INNER JOIN [dbo].[Rooms] r
	ON p.[Room] = r.[Id]
	WHERE r.[Area] = @area
	
	DELETE ar
	FROM [dbo].[CharacterActionRequirements] ar
	INNER JOIN [dbo].[Actions] a
	ON ar.[Action] = a.[Id]
	INNER JOIN [dbo].[Nouns] n
	ON a.[Noun] = n.[Id]
	INNER JOIN [dbo].[ParagraphStates] ps
	ON n.[ParagraphState] = ps.[Id]
	INNER JOIN [dbo].[Paragraphs] p
	ON ps.[Paragraph] = p.[Id]
	INNER JOIN [dbo].[Rooms] r
	ON p.[Room] = r.[Id]
	WHERE r.[Area] = @area
	
	DELETE ar
	FROM [dbo].[ActionResults] ar
	INNER JOIN [dbo].[Actions] a
	ON ar.[Action] = a.[Id]
	INNER JOIN [dbo].[Nouns] n
	ON a.[Noun] = n.[Id]
	INNER JOIN [dbo].[ParagraphStates] ps
	ON n.[ParagraphState] = ps.[Id]
	INNER JOIN [dbo].[Paragraphs] p
	ON ps.[Paragraph] = p.[Id]
	INNER JOIN [dbo].[Rooms] r
	ON p.[Room] = r.[Id]
	WHERE r.[Area] = @area
	
	DELETE a
	FROM [dbo].[Actions] a
	INNER JOIN [dbo].[Nouns] n
	ON a.[Noun] = n.[Id]
	INNER JOIN [dbo].[ParagraphStates] ps
	ON n.[ParagraphState] = ps.[Id]
	INNER JOIN [dbo].[Paragraphs] p
	ON ps.[Paragraph] = p.[Id]
	INNER JOIN [dbo].[Rooms] r
	ON p.[Room] = r.[Id]
	WHERE r.[Area] = @area

	DELETE n
	FROM [dbo].[Nouns] n
	INNER JOIN [dbo].[ParagraphStates] ps
	ON n.[ParagraphState] = ps.[Id]
	INNER JOIN [dbo].[Paragraphs] p
	ON ps.[Paragraph] = p.[Id]
	INNER JOIN [dbo].[Rooms] r
	ON p.[Room] = r.[Id]
	WHERE r.[Area] = @area

	DELETE ps
	FROM [dbo].[ParagraphStates] ps
	INNER JOIN [dbo].[Paragraphs] p
	ON ps.[Paragraph] = p.[Id]
	INNER JOIN [dbo].[Rooms] r
	ON p.[Room] = r.[Id]
	WHERE r.[Area] = @area

	DELETE p
	FROM [dbo].[Paragraphs] p
	INNER JOIN [dbo].[Rooms] r
	ON p.[Room] = r.[Id]
	WHERE r.[Area] = @area

	DELETE rs
	FROM [dbo].[RoomStates] rs
	INNER JOIN [dbo].[Rooms] r
	ON rs.[Room] = r.[Id]
	WHERE r.[Area] = @area

	DELETE
	FROM [dbo].[Rooms]
	WHERE [Area] = @area

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_DeleteAllRoomsInAreaOnFloor]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_DeleteAllRoomsInAreaOnFloor] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/16/2015
-- Description:	Deletes all Room records associated with the specified Area, on a specific floor (Z)
-- =============================================
ALTER PROCEDURE [dev].[dev_DeleteAllRoomsInAreaOnFloor]
	@area int,
	@z int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;
	
	DELETE ar
	FROM [dbo].[ItemActionRequirements] ar
	INNER JOIN [dbo].[Actions] a
	ON ar.[Action] = a.[Id]
	INNER JOIN [dbo].[Nouns] n
	ON a.[Noun] = n.[Id]
	INNER JOIN [dbo].[ParagraphStates] ps
	ON n.[ParagraphState] = ps.[Id]
	INNER JOIN [dbo].[Paragraphs] p
	ON ps.[Paragraph] = p.[Id]
	INNER JOIN [dbo].[Rooms] r
	ON p.[Room] = r.[Id]
	WHERE r.[Area] = @area
	AND r.[Z] = @z
	
	DELETE ar
	FROM [dbo].[EventActionRequirements] ar
	INNER JOIN [dbo].[Actions] a
	ON ar.[Action] = a.[Id]
	INNER JOIN [dbo].[Nouns] n
	ON a.[Noun] = n.[Id]
	INNER JOIN [dbo].[ParagraphStates] ps
	ON n.[ParagraphState] = ps.[Id]
	INNER JOIN [dbo].[Paragraphs] p
	ON ps.[Paragraph] = p.[Id]
	INNER JOIN [dbo].[Rooms] r
	ON p.[Room] = r.[Id]
	WHERE r.[Area] = @area
	AND r.[Z] = @z
	
	DELETE ar
	FROM [dbo].[CharacterActionRequirements] ar
	INNER JOIN [dbo].[Actions] a
	ON ar.[Action] = a.[Id]
	INNER JOIN [dbo].[Nouns] n
	ON a.[Noun] = n.[Id]
	INNER JOIN [dbo].[ParagraphStates] ps
	ON n.[ParagraphState] = ps.[Id]
	INNER JOIN [dbo].[Paragraphs] p
	ON ps.[Paragraph] = p.[Id]
	INNER JOIN [dbo].[Rooms] r
	ON p.[Room] = r.[Id]
	WHERE r.[Area] = @area
	AND r.[Z] = @z
	
	DELETE ar
	FROM [dbo].[ActionResults] ar
	INNER JOIN [dbo].[Actions] a
	ON ar.[Action] = a.[Id]
	INNER JOIN [dbo].[Nouns] n
	ON a.[Noun] = n.[Id]
	INNER JOIN [dbo].[ParagraphStates] ps
	ON n.[ParagraphState] = ps.[Id]
	INNER JOIN [dbo].[Paragraphs] p
	ON ps.[Paragraph] = p.[Id]
	INNER JOIN [dbo].[Rooms] r
	ON p.[Room] = r.[Id]
	WHERE r.[Area] = @area
	AND r.[Z] = @z
	
	DELETE a
	FROM [dbo].[Actions] a
	INNER JOIN [dbo].[Nouns] n
	ON a.[Noun] = n.[Id]
	INNER JOIN [dbo].[ParagraphStates] ps
	ON n.[ParagraphState] = ps.[Id]
	INNER JOIN [dbo].[Paragraphs] p
	ON ps.[Paragraph] = p.[Id]
	INNER JOIN [dbo].[Rooms] r
	ON p.[Room] = r.[Id]
	WHERE r.[Area] = @area
	AND r.[Z] = @z

	DELETE n
	FROM [dbo].[Nouns] n
	INNER JOIN [dbo].[ParagraphStates] ps
	ON n.[ParagraphState] = ps.[Id]
	INNER JOIN [dbo].[Paragraphs] p
	ON ps.[Paragraph] = p.[Id]
	INNER JOIN [dbo].[Rooms] r
	ON p.[Room] = r.[Id]
	WHERE r.[Area] = @area
	AND r.[Z] = @z

	DELETE ps
	FROM [dbo].[ParagraphStates] ps
	INNER JOIN [dbo].[Paragraphs] p
	ON ps.[Paragraph] = p.[Id]
	INNER JOIN [dbo].[Rooms] r
	ON p.[Room] = r.[Id]
	WHERE r.[Area] = @area
	AND r.[Z] = @z

	DELETE p
	FROM [dbo].[Paragraphs] p
	INNER JOIN [dbo].[Rooms] r
	ON p.[Room] = r.[Id]
	WHERE r.[Area] = @area
	AND r.[Z] = @z

	DELETE rs
	FROM [dbo].[RoomStates] rs
	INNER JOIN [dbo].[Rooms] r
	ON rs.[Room] = r.[Id]
	WHERE r.[Area] = @area
	AND r.[Z] = @z

	DELETE
	FROM [dbo].[Rooms]
	WHERE [Area] = @area
	AND [Z] = @z


END
GO

/******************************************************************************************************************************************/
/*RoomState********************************************************************************************************************************/
/******************************************************************************************************************************************/

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_AddRoomState]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_AddRoomState] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/12/2015
-- Description:	Adds a RoomState record and returns the newly generated ID
-- =============================================
ALTER PROCEDURE [dev].[dev_AddRoomState]
	@time datetime,
	@location int,
	@room int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

    DECLARE @newstate int
    SELECT @newstate = ISNULL(MAX([State]), -1) + 1
    FROM [dbo].[RoomStates]
    WHERE [Room] = @room
    
	INSERT INTO [dbo].[RoomStates] ([State], [Time], [Location], [Room])
	VALUES (@newstate, @time, @location, @room)
	
	SELECT SCOPE_IDENTITY()

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_UpdateRoomState]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_UpdateRoomState] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/12/2015
-- Description:	Updates a RoomState record
-- =============================================
ALTER PROCEDURE [dev].[dev_UpdateRoomState]
	@id int,
	@state int,
	@time datetime,
	@location int,
	@room int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	UPDATE [dbo].[RoomStates] 
	SET	[State] = ISNULL(@state, [State]), 
		[Time] = @time,
		[Location] = ISNULL(@location, [Location]),
		[Room] = ISNULL(@room, [Room])
	WHERE [Id] = @id

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_GetAllRoomStatesForRoom]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_GetAllRoomStatesForRoom] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/19/2015
-- Description:	Gets all RoomState records associated with the specified Room
-- =============================================
ALTER PROCEDURE [dev].[dev_GetAllRoomStatesForRoom]
	@room int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [Id],
		   [State],
		   [Time],
		   [Location],
		   [Room]
	FROM [dbo].[RoomStates]
	WHERE [Room] = @room

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_GetRoomState]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_GetRoomState] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/21/2015
-- Description:	Gets data about an RoomState record in the database
-- =============================================
ALTER PROCEDURE [dev].[dev_GetRoomState]
	@id int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [Id],
		   [State],
		   [Time],
		   [Location],
		   [Room]
	FROM [dbo].[RoomStates]
	WHERE [Id] = @id

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_DeleteAllRoomStatesForRoom]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_DeleteAllRoomStatesForRoom] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/16/2015
-- Description:	Deletes all RoomState records associated with the specified Room
-- =============================================
ALTER PROCEDURE [dev].[dev_DeleteAllRoomStatesForRoom]
	@room int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;
	
	DELETE ar
	FROM [dbo].[ItemActionRequirements] ar
	INNER JOIN [dbo].[Actions] a
	ON ar.[Action] = a.[Id]
	INNER JOIN [dbo].[Nouns] n
	ON a.[Noun] = n.[Id]
	INNER JOIN [dbo].[ParagraphStates] ps
	ON n.[ParagraphState] = ps.[Id]
	INNER JOIN [dbo].[Paragraphs] p
	ON ps.[Paragraph] = p.[Id]
	INNER JOIN [dbo].[RoomStates] rs
	ON p.[RoomState] = rs.[Id]
	WHERE rs.[Room] = @room
	
	DELETE ar
	FROM [dbo].[EventActionRequirements] ar
	INNER JOIN [dbo].[Actions] a
	ON ar.[Action] = a.[Id]
	INNER JOIN [dbo].[Nouns] n
	ON a.[Noun] = n.[Id]
	INNER JOIN [dbo].[ParagraphStates] ps
	ON n.[ParagraphState] = ps.[Id]
	INNER JOIN [dbo].[Paragraphs] p
	ON ps.[Paragraph] = p.[Id]
	INNER JOIN [dbo].[RoomStates] rs
	ON p.[RoomState] = rs.[Id]
	WHERE rs.[Room] = @room
	
	DELETE ar
	FROM [dbo].[CharacterActionRequirements] ar
	INNER JOIN [dbo].[Actions] a
	ON ar.[Action] = a.[Id]
	INNER JOIN [dbo].[Nouns] n
	ON a.[Noun] = n.[Id]
	INNER JOIN [dbo].[ParagraphStates] ps
	ON n.[ParagraphState] = ps.[Id]
	INNER JOIN [dbo].[Paragraphs] p
	ON ps.[Paragraph] = p.[Id]
	INNER JOIN [dbo].[RoomStates] rs
	ON p.[RoomState] = rs.[Id]
	WHERE rs.[Room] = @room
	
	DELETE ar
	FROM [dbo].[ActionResults] ar
	INNER JOIN [dbo].[Actions] a
	ON ar.[Action] = a.[Id]
	INNER JOIN [dbo].[Nouns] n
	ON a.[Noun] = n.[Id]
	INNER JOIN [dbo].[ParagraphStates] ps
	ON n.[ParagraphState] = ps.[Id]
	INNER JOIN [dbo].[Paragraphs] p
	ON ps.[Paragraph] = p.[Id]
	INNER JOIN [dbo].[RoomStates] rs
	ON p.[RoomState] = rs.[Id]
	WHERE rs.[Room] = @room
	
	DELETE a
	FROM [dbo].[Actions] a
	INNER JOIN [dbo].[Nouns] n
	ON a.[Noun] = n.[Id]
	INNER JOIN [dbo].[ParagraphStates] ps
	ON n.[ParagraphState] = ps.[Id]
	INNER JOIN [dbo].[Paragraphs] p
	ON ps.[Paragraph] = p.[Id]
	INNER JOIN [dbo].[RoomStates] rs
	ON p.[RoomState] = rs.[Id]
	WHERE rs.[Room] = @room

	DELETE n
	FROM [dbo].[Nouns] n
	INNER JOIN [dbo].[ParagraphStates] ps
	ON n.[ParagraphState] = ps.[Id]
	INNER JOIN [dbo].[Paragraphs] p
	ON ps.[Paragraph] = p.[Id]
	INNER JOIN [dbo].[RoomStates] rs
	ON p.[RoomState] = rs.[Id]
	WHERE rs.[Room] = @room

	DELETE ps
	FROM [dbo].[ParagraphStates] ps
	INNER JOIN [dbo].[Paragraphs] p
	ON ps.[Paragraph] = p.[Id]
	INNER JOIN [dbo].[RoomStates] rs
	ON p.[RoomState] = rs.[Id]
	WHERE rs.[Room] = @room

	DELETE p
	FROM [dbo].[Paragraphs] p
	INNER JOIN [dbo].[RoomStates] rs
	ON p.[RoomState] = rs.[Id]
	WHERE rs.[Room] = @room

	DELETE
	FROM [dbo].[RoomStates]
	WHERE [Room] = @room

END
GO

/******************************************************************************************************************************************/
/*Paragraph********************************************************************************************************************************/
/******************************************************************************************************************************************/

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_AddParagraph]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_AddParagraph] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/12/2015
-- Description:	Adds a Paragraph record and returns the newly generated ID
-- =============================================
ALTER PROCEDURE [dev].[dev_AddParagraph]
	@order int,
	@room int,
	@roomstate int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;
    
	INSERT INTO [dbo].[Paragraphs] ([Order], [Room], [RoomState])
	VALUES (@order, @room, @roomstate)
	
	SELECT SCOPE_IDENTITY()

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_UpdateParagraph]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_UpdateParagraph] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/12/2015
-- Description:	Updates a Paragraph record
-- =============================================
ALTER PROCEDURE [dev].[dev_UpdateParagraph]
	@id int,
	@order int,
	@room int,
	@roomstate int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	UPDATE [dbo].[Paragraphs] 
	SET	[Order] = ISNULL(@order, [Order]),
		[Room] = ISNULL(@room, [Room]),
		[RoomState] = @roomState
	WHERE [Id] = @id

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_GetAllParagraphsForRoomAndRoomState]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_GetAllParagraphsForRoomAndRoomState] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/27/2015
-- Description:	Gets all Paragraph records associated with the specified Room and RoomState
-- =============================================
ALTER PROCEDURE [dev].[dev_GetAllParagraphsForRoomAndRoomState]
	@room int,
	@roomstate int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [Id],
		   [Order],
		   [Room],
		   [RoomState]
	FROM [dbo].[Paragraphs]
	WHERE [Room] = @room
	AND ([RoomState] = @roomstate OR [RoomState] IS NULL)
	ORDER BY [Order]

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_GetParagraph]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_GetParagraph] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/21/2015
-- Description:	Gets data about an Paragraph record in the database
-- =============================================
ALTER PROCEDURE [dev].[dev_GetParagraph]
	@id int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [Id],
		   [Order],
		   [Room],
		   [RoomState]
	FROM [dbo].[Paragraphs]
	WHERE [Id] = @id

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_DeleteAllParagraphsForRoomAndRoomState]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_DeleteAllParagraphsForRoomAndRoomState] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/16/2015
-- Description:	Deletes all Paragraph records associated with the specified Room and RoomState
-- =============================================
ALTER PROCEDURE [dev].[dev_DeleteAllParagraphsForRoomAndRoomState]
	@room int,
	@roomstate int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;
	
	DELETE ar
	FROM [dbo].[ItemActionRequirements] ar
	INNER JOIN [dbo].[Actions] a
	ON ar.[Action] = a.[Id]
	INNER JOIN [dbo].[Nouns] n
	ON a.[Noun] = n.[Id]
	INNER JOIN [dbo].[ParagraphStates] ps
	ON n.[ParagraphState] = ps.[Id]
	INNER JOIN [dbo].[Paragraphs] p
	ON ps.[Paragraph] = p.[Id]
	WHERE p.[Room] = @room
	AND (p.[RoomState] = @roomstate OR p.[RoomState] IS NULL)
	
	DELETE ar
	FROM [dbo].[EventActionRequirements] ar
	INNER JOIN [dbo].[Actions] a
	ON ar.[Action] = a.[Id]
	INNER JOIN [dbo].[Nouns] n
	ON a.[Noun] = n.[Id]
	INNER JOIN [dbo].[ParagraphStates] ps
	ON n.[ParagraphState] = ps.[Id]
	INNER JOIN [dbo].[Paragraphs] p
	ON ps.[Paragraph] = p.[Id]
	WHERE p.[Room] = @room
	AND (p.[RoomState] = @roomstate OR p.[RoomState] IS NULL)
	
	DELETE ar
	FROM [dbo].[CharacterActionRequirements] ar
	INNER JOIN [dbo].[Actions] a
	ON ar.[Action] = a.[Id]
	INNER JOIN [dbo].[Nouns] n
	ON a.[Noun] = n.[Id]
	INNER JOIN [dbo].[ParagraphStates] ps
	ON n.[ParagraphState] = ps.[Id]
	INNER JOIN [dbo].[Paragraphs] p
	ON ps.[Paragraph] = p.[Id]
	WHERE p.[Room] = @room
	AND (p.[RoomState] = @roomstate OR p.[RoomState] IS NULL)
	
	DELETE ar
	FROM [dbo].[ActionResults] ar
	INNER JOIN [dbo].[Actions] a
	ON ar.[Action] = a.[Id]
	INNER JOIN [dbo].[Nouns] n
	ON a.[Noun] = n.[Id]
	INNER JOIN [dbo].[ParagraphStates] ps
	ON n.[ParagraphState] = ps.[Id]
	INNER JOIN [dbo].[Paragraphs] p
	ON ps.[Paragraph] = p.[Id]
	WHERE p.[Room] = @room
	AND (p.[RoomState] = @roomstate OR p.[RoomState] IS NULL)
	
	DELETE a
	FROM [dbo].[Actions] a
	INNER JOIN [dbo].[Nouns] n
	ON a.[Noun] = n.[Id]
	INNER JOIN [dbo].[ParagraphStates] ps
	ON n.[ParagraphState] = ps.[Id]
	INNER JOIN [dbo].[Paragraphs] p
	ON ps.[Paragraph] = p.[Id]
	WHERE p.[Room] = @room
	AND (p.[RoomState] = @roomstate OR p.[RoomState] IS NULL)

	DELETE n
	FROM [dbo].[Nouns] n
	INNER JOIN [dbo].[ParagraphStates] ps
	ON n.[ParagraphState] = ps.[Id]
	INNER JOIN [dbo].[Paragraphs] p
	ON ps.[Paragraph] = p.[Id]
	WHERE p.[Room] = @room
	AND (p.[RoomState] = @roomstate OR p.[RoomState] IS NULL)

	DELETE ps
	FROM [dbo].[ParagraphStates] ps
	INNER JOIN [dbo].[Paragraphs] p
	ON ps.[Paragraph] = p.[Id]
	WHERE p.[Room] = @room
	AND (p.[RoomState] = @roomstate OR p.[RoomState] IS NULL)

	DELETE
	FROM [dbo].[Paragraphs]
	WHERE [Room] = @room
	AND ([RoomState] = @roomstate OR [RoomState] IS NULL)

END
GO

/******************************************************************************************************************************************/
/*ParagraphState***************************************************************************************************************************/
/******************************************************************************************************************************************/

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_AddParagraphState]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_AddParagraphState] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/1/2015
-- Description:	Adds a ParagraphState record and returns the newly generated ID
-- =============================================
ALTER PROCEDURE [dev].[dev_AddParagraphState]
	@text varchar(MAX),
	@paragraph int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;
    
    DECLARE @newstate int
    SELECT @newstate = ISNULL(MAX([State]), -1) + 1
    FROM [dbo].[ParagraphStates]
    WHERE [Paragraph] = @paragraph
    
	INSERT INTO [dbo].[ParagraphStates] ([Text], [State], [Paragraph])
	VALUES (@text, @newstate, @paragraph)
	
	SELECT SCOPE_IDENTITY()

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_UpdateParagraphState]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_UpdateParagraphState] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/1/2015
-- Description:	Updates a ParagraphState record
-- =============================================
ALTER PROCEDURE [dev].[dev_UpdateParagraphState]
	@id int,
	@text varchar(MAX),
	@state int,
	@paragraph int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	UPDATE [dbo].[ParagraphStates] 
	SET	[Text] = ISNULL(@text, [Text]),
		[State] = ISNULL(@state, [State]),
		[Paragraph] = ISNULL(@paragraph, [Paragraph])
	WHERE [Id] = @id

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_GetAllParagraphStatesForParagraph]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_GetAllParagraphStatesForParagraph] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/1/2015
-- Description:	Gets all ParagraphState records associated with a specified Paragraph
-- =============================================
ALTER PROCEDURE [dev].[dev_GetAllParagraphStatesForParagraph]
	@paragraph int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [Id],
		   [Text],
		   [State],
		   [Paragraph]
	FROM [dbo].[ParagraphStates]
	WHERE [Paragraph] = @paragraph
	ORDER BY [State]

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_GetParagraphState]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_GetParagraphState] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/1/2015
-- Description:	Gets data about a ParagraphState record in the database
-- =============================================
ALTER PROCEDURE [dev].[dev_GetParagraphState]
	@id int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [Id],
		   [Text],
		   [State],
		   [Paragraph]
	FROM [dbo].[ParagraphStates]
	WHERE [Id] = @id

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_DeleteAllParagraphStatesForParagraph]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_DeleteAllParagraphStatesForParagraph] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/16/2015
-- Description:	Deletes all ParagraphState records associated with a specified Paragraph
-- =============================================
ALTER PROCEDURE [dev].[dev_DeleteAllParagraphStatesForParagraph]
	@paragraph int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;
	
	DELETE ar
	FROM [dbo].[ItemActionRequirements] ar
	INNER JOIN [dbo].[Actions] a
	ON ar.[Action] = a.[Id]
	INNER JOIN [dbo].[Nouns] n
	ON a.[Noun] = n.[Id]
	INNER JOIN [dbo].[ParagraphStates] ps
	ON n.[ParagraphState] = ps.[Id]
	WHERE ps.[Paragraph] = @paragraph
	
	DELETE ar
	FROM [dbo].[EventActionRequirements] ar
	INNER JOIN [dbo].[Actions] a
	ON ar.[Action] = a.[Id]
	INNER JOIN [dbo].[Nouns] n
	ON a.[Noun] = n.[Id]
	INNER JOIN [dbo].[ParagraphStates] ps
	ON n.[ParagraphState] = ps.[Id]
	WHERE ps.[Paragraph] = @paragraph
	
	DELETE ar
	FROM [dbo].[CharacterActionRequirements] ar
	INNER JOIN [dbo].[Actions] a
	ON ar.[Action] = a.[Id]
	INNER JOIN [dbo].[Nouns] n
	ON a.[Noun] = n.[Id]
	INNER JOIN [dbo].[ParagraphStates] ps
	ON n.[ParagraphState] = ps.[Id]
	WHERE ps.[Paragraph] = @paragraph
	
	DELETE ar
	FROM [dbo].[ActionResults] ar
	INNER JOIN [dbo].[Actions] a
	ON ar.[Action] = a.[Id]
	INNER JOIN [dbo].[Nouns] n
	ON a.[Noun] = n.[Id]
	INNER JOIN [dbo].[ParagraphStates] ps
	ON n.[ParagraphState] = ps.[Id]
	WHERE ps.[Paragraph] = @paragraph
	
	DELETE a
	FROM [dbo].[Actions] a
	INNER JOIN [dbo].[Nouns] n
	ON a.[Noun] = n.[Id]
	INNER JOIN [dbo].[ParagraphStates] ps
	ON n.[ParagraphState] = ps.[Id]
	WHERE ps.[Paragraph] = @paragraph

	DELETE n
	FROM [dbo].[Nouns] n
	INNER JOIN [dbo].[ParagraphStates] ps
	ON n.[ParagraphState] = ps.[Id]
	WHERE ps.[Paragraph] = @paragraph

	DELETE
	FROM [dbo].[ParagraphStates]
	WHERE [Paragraph] = @paragraph

END
GO

/******************************************************************************************************************************************/
/*Noun*************************************************************************************************************************************/
/******************************************************************************************************************************************/

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_AddNoun]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_AddNoun] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/12/2015
-- Description:	Adds a Noun record, checking to ensure that the specified text value IS present in the ParagraphState, 
-- and returns the newly generated ID
-- =============================================
ALTER PROCEDURE [dev].[dev_AddNoun]
	@text varchar(MAX),
	@paragraphstate int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;
	
	IF NOT EXISTS (SELECT 1
				   FROM [dbo].[ParagraphStates] p
				   WHERE p.[Id] = @paragraphstate AND p.[Text] LIKE '%' + @text + '%')
	BEGIN
		RAISERROR (N'The [Text] value of a Noun must be present in the [Text] value of the ParagraphState to which it is associated.',
				   1,
				   1)
	END

	INSERT INTO [dbo].[Nouns] ([Text], [ParagraphState])
	VALUES (@text, @paragraphstate)
	
	SELECT SCOPE_IDENTITY()

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_UpdateNoun]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_UpdateNoun] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/2/2015
-- Description:	Updates a Noun record
-- =============================================
ALTER PROCEDURE [dev].[dev_UpdateNoun]
	@id int,
	@text varchar(MAX),
	@paragraphstate int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	UPDATE [dbo].[Nouns] 
	SET	[Text] = ISNULL(@text, [Text]),
		[ParagraphState] = ISNULL(@paragraphstate, [ParagraphState])
	WHERE [Id] = @id

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_GetAllNounsForParagraphState]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_GetAllNounsForParagraphState] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/2/2015
-- Description:	Gets all Noun records associated with a specified ParagraphState
-- =============================================
ALTER PROCEDURE [dev].[dev_GetAllNounsForParagraphState]
	@paragraphstate int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [Id],
		   [Text],
		   [ParagraphState]
	FROM [dbo].[Nouns]
	WHERE [ParagraphState] = @paragraphstate

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_GetNoun]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_GetNoun] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/2/2015
-- Description:	Gets data about a Noun record in the database
-- =============================================
ALTER PROCEDURE [dev].[dev_GetNoun]
	@id int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [Id],
		   [Text],
		   [ParagraphState]
	FROM [dbo].[Nouns]
	WHERE [Id] = @id

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_DeleteAllNounsForParagraphState]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_DeleteAllNounsForParagraphState] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/16/2015
-- Description:	Deletes all Noun records associated with a specified ParagraphState
-- =============================================
ALTER PROCEDURE [dev].[dev_DeleteAllNounsForParagraphState]
	@paragraphstate int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;
	
	DELETE ar
	FROM [dbo].[ItemActionRequirements] ar
	INNER JOIN [dbo].[Actions] a
	ON ar.[Action] = a.[Id]
	INNER JOIN [dbo].[Nouns] n
	ON a.[Noun] = n.[Id]
	WHERE n.[ParagraphState] = @paragraphstate
	
	DELETE ar
	FROM [dbo].[EventActionRequirements] ar
	INNER JOIN [dbo].[Actions] a
	ON ar.[Action] = a.[Id]
	INNER JOIN [dbo].[Nouns] n
	ON a.[Noun] = n.[Id]
	WHERE n.[ParagraphState] = @paragraphstate
	
	DELETE ar
	FROM [dbo].[CharacterActionRequirements] ar
	INNER JOIN [dbo].[Actions] a
	ON ar.[Action] = a.[Id]
	INNER JOIN [dbo].[Nouns] n
	ON a.[Noun] = n.[Id]
	WHERE n.[ParagraphState] = @paragraphstate
	
	DELETE ar
	FROM [dbo].[ActionResults] ar
	INNER JOIN [dbo].[Actions] a
	ON ar.[Action] = a.[Id]
	INNER JOIN [dbo].[Nouns] n
	ON a.[Noun] = n.[Id]
	WHERE n.[ParagraphState] = @paragraphstate
	
	DELETE a
	FROM [dbo].[Actions] a
	INNER JOIN [dbo].[Nouns] n
	ON a.[Noun] = n.[Id]
	WHERE n.[ParagraphState] = @paragraphstate

	DELETE
	FROM [dbo].[Nouns]
	WHERE [ParagraphState] = @paragraphstate

END
GO

/******************************************************************************************************************************************/
/*VerbType*********************************************************************************************************************************/
/******************************************************************************************************************************************/

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_AddVerbType]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_AddVerbType] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/12/2015
-- Description:	Adds a VerbType record and returns the newly generated ID
-- =============================================
ALTER PROCEDURE [dev].[dev_AddVerbType]
	@name varchar(500)
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	INSERT INTO [dbo].[VerbTypes] ([Name])
	VALUES (@name)
	
	SELECT SCOPE_IDENTITY()

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_UpdateVerbType]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_UpdateVerbType] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/12/2015
-- Description:	Updates a VerbType record
-- =============================================
ALTER PROCEDURE [dev].[dev_UpdateVerbType]
	@id int,
	@name varchar(500)
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	UPDATE [dbo].[VerbTypes] 
	SET	[Name] = ISNULL(@name, [Name])
	WHERE [Id] = @id

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_GetAllVerbTypes]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_GetAllVerbTypes] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/2/2015
-- Description:	Gets the Id and Name fields of all VerbType records currently in the database
-- =============================================
ALTER PROCEDURE [dev].[dev_GetAllVerbTypes]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [Id],
		   [Name]
	FROM [dbo].[VerbTypes]

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_GetVerbType]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_GetVerbType] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/2/2015
-- Description:	Gets data about a VerbType record in the database
-- =============================================
ALTER PROCEDURE [dev].[dev_GetVerbType]
	@id int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [Id],
		   [Name]
	FROM [dbo].[VerbTypes]
	WHERE [Id] = @id

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_DeleteAllVerbTypes]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_DeleteAllVerbTypes] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/16/2015
-- Description:	Deletes the Id and Name fields of all VerbType records currently in the database
-- =============================================
ALTER PROCEDURE [dev].[dev_DeleteAllVerbTypes]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;
	
	DELETE
	FROM [dbo].[MessageChoiceResults]
	
	DELETE
	FROM [dbo].[ActionResults]
	
	DELETE
	FROM [dbo].[Results]
	
	DELETE
	FROM [dev].[ResultTypeJSONProperties]
	
	DELETE
	FROM [dbo].[ResultTypes]
	
	DELETE
	FROM [dbo].[ItemActionRequirements]
	
	DELETE
	FROM [dbo].[EventActionRequirements]
	
	DELETE
	FROM [dbo].[CharacterActionRequirements]
	
	DELETE
	FROM [dbo].[Actions]
	
	DELETE
	FROM [dbo].[Verbs]

	DELETE
	FROM [dbo].[VerbTypes]
	
	DBCC CHECKIDENT ('[dbo].[MessageChoiceResults]', RESEED, 0)
	DBCC CHECKIDENT ('[dbo].[ActionResults]', RESEED, 0)
	DBCC CHECKIDENT ('[dbo].[Results]', RESEED, 0)
	DBCC CHECKIDENT ('[dev].[ResultTypeJSONProperties]', RESEED, 0)
	DBCC CHECKIDENT ('[dbo].[ResultTypes]', RESEED, 0)
	DBCC CHECKIDENT ('[dbo].[ItemActionRequirements]', RESEED, 0)
	DBCC CHECKIDENT ('[dbo].[EventActionRequirements]', RESEED, 0)
	DBCC CHECKIDENT ('[dbo].[CharacterActionRequirements]', RESEED, 0)
	DBCC CHECKIDENT ('[dbo].[Actions]', RESEED, 0)
	DBCC CHECKIDENT ('[dbo].[Verbs]', RESEED, 0)
	DBCC CHECKIDENT ('[dbo].[VerbTypes]', RESEED, 0)

END
GO

/******************************************************************************************************************************************/
/*Verb*************************************************************************************************************************************/
/******************************************************************************************************************************************/

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_AddVerb]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_AddVerb] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/12/2015
-- Description:	Adds a Verb record and returns the newly generated ID
-- =============================================
ALTER PROCEDURE [dev].[dev_AddVerb]
	@name varchar(500),
	@verbtype int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	INSERT INTO [dbo].[Verbs] ([Name], [VerbType])
	VALUES (@name, @verbtype)
	
	SELECT SCOPE_IDENTITY()

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_UpdateVerb]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_UpdateVerb] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/12/2015
-- Description:	Updates a Verb record
-- =============================================
ALTER PROCEDURE [dev].[dev_UpdateVerb]
	@id int,
	@name varchar(500),
	@verbtype int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	UPDATE [dbo].[Verbs] 
	SET	[Name] = ISNULL(@name, [Name]),
		[VerbType] = ISNULL(@verbtype, [VerbType])
	WHERE [Id] = @id

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_GetAllVerbsForVerbType]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_GetAllVerbsForVerbType] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/2/2015
-- Description:	Gets all Verb records associated with a specified VerbType
-- =============================================
ALTER PROCEDURE [dev].[dev_GetAllVerbsForVerbType]
	@verbtype int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [Id],
		   [Name],
		   [VerbType]
	FROM [dbo].[Verbs]
	WHERE [VerbType] = @verbtype

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_GetVerb]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_GetVerb] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/2/2015
-- Description:	Gets data about a Verb record in the database
-- =============================================
ALTER PROCEDURE [dev].[dev_GetVerb]
	@id int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [Id],
		   [Name],
		   [VerbType]
	FROM [dbo].[Verbs]
	WHERE [Id] = @id

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_DeleteAllVerbsForVerbType]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_DeleteAllVerbsForVerbType] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/16/2015
-- Description:	Deletes all Verb records associated with a specified VerbType
-- =============================================
ALTER PROCEDURE [dev].[dev_DeleteAllVerbsForVerbType]
	@verbtype int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	DELETE
	FROM [dbo].[Verbs]
	WHERE [VerbType] = @verbtype

END
GO

/******************************************************************************************************************************************/
/*ResultType*******************************************************************************************************************************/
/******************************************************************************************************************************************/

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_AddResultType]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_AddResultType] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/12/2015
-- Description:	Adds a ResultType record and returns the newly generated ID
-- =============================================
ALTER PROCEDURE [dev].[dev_AddResultType]
	@name varchar(500)
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	INSERT INTO [dbo].[ResultTypes] ([Name])
	VALUES (@name)
	
	SELECT SCOPE_IDENTITY()

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_UpdateResultType]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_UpdateResultType] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/12/2015
-- Description:	Updates a ResultType record
-- =============================================
ALTER PROCEDURE [dev].[dev_UpdateResultType]
	@id int,
	@name varchar(500)
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	UPDATE [dbo].[ResultTypes] 
	SET	[Name] = ISNULL(@name, [Name])
	WHERE [Id] = @id

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_GetAllResultTypes]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_GetAllResultTypes] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/3/2015
-- Description:	Gets the Id and Name fields of all ResultType records currently in the database
-- =============================================
ALTER PROCEDURE [dev].[dev_GetAllResultTypes]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [Id],
		   [Name]
	FROM [dbo].[ResultTypes]

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_GetResultType]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_GetResultType] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/3/2015
-- Description:	Gets data about a ResultType record in the database
-- =============================================
ALTER PROCEDURE [dev].[dev_GetResultType]
	@id int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [Id],
		   [Name]
	FROM [dbo].[ResultTypes]
	WHERE [Id] = @id

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_DeleteAllResultTypes]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_DeleteAllResultTypes] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/16/2015
-- Description:	Deletes the Id and Name fields of all ResultType records currently in the database
-- =============================================
ALTER PROCEDURE [dev].[dev_DeleteAllResultTypes]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;
	
	DELETE
	FROM [dbo].[ActionResults]
	
	DELETE
	FROM [dbo].[MessageChoiceResults]
	
	DELETE
	FROM [dev].[ResultNames]
	
	DELETE
	FROM [dbo].[Results]
	
	DELETE
	FROM [dev].[ResultTypeJSONProperties]

	DELETE
	FROM [dbo].[ResultTypes]
	
	DBCC CHECKIDENT ('[dbo].[ActionResults]', RESEED, 0)
	DBCC CHECKIDENT ('[dbo].[MessageChoiceResults]', RESEED, 0)
	DBCC CHECKIDENT ('[dbo].[Results]', RESEED, 0)
	DBCC CHECKIDENT ('[dev].[ResultTypeJSONProperties]', RESEED, 0)
	DBCC CHECKIDENT ('[dbo].[ResultTypes]', RESEED, 0)

END
GO

/******************************************************************************************************************************************/
/*ResultTypeJSONProperty*******************************************************************************************************************/
/******************************************************************************************************************************************/

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_AddResultTypeJSONProperty]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_AddResultTypeJSONProperty] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/4/2015
-- Description:	Adds a ResultTypeJSONProperty record and returns the newly generated ID
-- =============================================
ALTER PROCEDURE [dev].[dev_AddResultTypeJSONProperty]
	@jsonproperty varchar(MAX),
	@resulttype int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	INSERT INTO [dev].[ResultTypeJSONProperties] ([JSONProperty], [ResultType])
	VALUES (@jsonproperty, @resulttype)
	
	SELECT SCOPE_IDENTITY()

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_UpdateResultTypeJSONProperty]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_UpdateResultTypeJSONProperty] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/4/2015
-- Description:	Updates a ResultTypeJSONProperty record
-- =============================================
ALTER PROCEDURE [dev].[dev_UpdateResultTypeJSONProperty]
	@id int,
	@jsonproperty varchar(MAX),
	@resulttype int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	UPDATE [dev].[ResultTypeJSONProperties] 
	SET	[JSONProperty] = ISNULL(@jsonproperty, [JSONProperty]),
		[ResultType] = ISNULL(@resulttype, [ResultType])
	WHERE [Id] = @id

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_GetAllResultTypeJSONPropertiesForResultType]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_GetAllResultTypeJSONPropertiesForResultType] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/4/2015
-- Description:	Gets the all ResultTypeJSONProperties records associated with the specified ResultType
-- =============================================
ALTER PROCEDURE [dev].[dev_GetAllResultTypeJSONPropertiesForResultType]
	@resulttype int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [Id],
		   [JSONProperty],
		   [ResultType]
	FROM [dev].[ResultTypeJSONProperties]
	WHERE [ResultType] = @resulttype

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_GetResultTypeJSONProperty]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_GetResultTypeJSONProperty] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/4/2015
-- Description:	Gets data about a ResultTypeJSONProperty record in the database
-- =============================================
ALTER PROCEDURE [dev].[dev_GetResultTypeJSONProperty]
	@id int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [Id],
		   [JSONProperty],
		   [ResultType]
	FROM [dev].[ResultTypeJSONProperties]
	WHERE [Id] = @id

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_DeleteAllResultTypeJSONPropertiesForResultType]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_DeleteAllResultTypeJSONPropertiesForResultType] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/16/2015
-- Description:	Deletes the all ResultTypeJSONProperties records associated with the specified ResultType
-- =============================================
ALTER PROCEDURE [dev].[dev_DeleteAllResultTypeJSONPropertiesForResultType]
	@resulttype int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	DELETE
	FROM [dev].[ResultTypeJSONProperties]
	WHERE [ResultType] = @resulttype

END
GO

/******************************************************************************************************************************************/
/*Result***********************************************************************************************************************************/
/******************************************************************************************************************************************/

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_AddResult]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_AddResult] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/4/2015
-- Description:	Adds a Result record and returns the newly generated ID
-- =============================================
ALTER PROCEDURE [dev].[dev_AddResult]
	@name varchar(500),
	@jsondata varchar(MAX),
	@resulttype int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	DECLARE @resultid decimal

	INSERT INTO [dbo].[Results] ([JSONData], [ResultType])
	VALUES (@jsondata, @resulttype)
	
	SELECT @resultid = SCOPE_IDENTITY()
	
	INSERT INTO [dev].[ResultNames] ([Result], [Name])
	VALUES(@resultid, @name)
	
	SELECT @resultid

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_UpdateResult]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_UpdateResult] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/4/2015
-- Description:	Updates a Result record
-- =============================================
ALTER PROCEDURE [dev].[dev_UpdateResult]
	@id int,
	@name varchar(500),
	@jsondata varchar(MAX),
	@resulttype int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	UPDATE [dbo].[Results] 
	SET	[JSONData] = @jsondata, 
		[ResultType] = ISNULL(@resulttype, [ResultType])
	WHERE [Id] = @id
	
	UPDATE [dev].[ResultNames]
	SET [Name] = ISNULL(@name, [Name])
	WHERE [Result] = @id

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_GetAllResultsForResultType]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_GetAllResultsForResultType] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/4/2015
-- Description:	Gets all Result records associated with a specified ResultType
-- =============================================
ALTER PROCEDURE [dev].[dev_GetAllResultsForResultType]
	@resulttype int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [Id],
		   [Name],
		   [JSONData],
		   [ResultType]
	FROM [dev].[Results] r
	WHERE [ResultType] = @resulttype

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_GetAllResultsForActionResultType]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_GetAllResultsForActionResultType] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/9/2015
-- Description:	Gets all Result records associated with all ResultTypes associated with the specified Action
-- =============================================
ALTER PROCEDURE [dev].[dev_GetAllResultsForActionResultType]
	@action int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT r.[Id],
		   r.[Name],
		   r.[JSONData],
		   r.[ResultType]
	FROM [dev].[Results] r
	INNER JOIN [dev].[ActionResultTypes] art
	ON r.[ResultType] = art.[ResultType]
	WHERE art.[Action] = @action

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_GetAllResultsForMessageChoiceResultType]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_GetAllResultsForMessageChoiceResultType] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/15/2015
-- Description:	Gets all Result records associated with all ResultTypes associated with the specified MessageChoice
-- =============================================
ALTER PROCEDURE [dev].[dev_GetAllResultsForMessageChoiceResultType]
	@messagechoice int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT r.[Id],
		   r.[Name],
		   r.[JSONData],
		   r.[ResultType]
	FROM [dev].[Results] r
	INNER JOIN [dev].[MessageChoiceResultTypes] mcrt
	ON r.[ResultType] = mcrt.[ResultType]
	WHERE mcrt.[MessageChoice] = @messagechoice

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_GetResult]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_GetResult] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/4/2015
-- Description:	Get a Result record in the database
-- =============================================
ALTER PROCEDURE [dev].[dev_GetResult]
	@id int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [Id],
		   [Name],
		   [JSONData],
		   [ResultType]
	FROM [dev].[Results]
	WHERE [Id] = @id

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_DeleteAllResultsForResultType]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_DeleteAllResultsForResultType] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/16/2015
-- Description:	Deletes all Result records associated with a specified ResultType
-- =============================================
ALTER PROCEDURE [dev].[dev_DeleteAllResultsForResultType]
	@resulttype int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	DELETE rn
	FROM [dev].[ResultNames] rn
	INNER JOIN [dbo].[Results] r
	ON rn.[Result] = r.[Id]
	WHERE r.[ResultType] = @resulttype

	DELETE
	FROM [dbo].[Results]
	WHERE [ResultType] = @resulttype

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_DeleteAllResultsForActionResultType]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_DeleteAllResultsForActionResultType] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/16/2015
-- Description:	Deletes all Result records associated with all ResultTypes associated with the specified Action
-- =============================================
ALTER PROCEDURE [dev].[dev_DeleteAllResultsForActionResultType]
	@action int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	DELETE rn
	FROM [dev].[ResultNames] rn
	INNER JOIN [dbo].[Results] r
	ON rn.[Result] = r.[Id]
	INNER JOIN [dev].[ActionResultTypes] art
	ON r.[ResultType] = art.[ResultType]
	WHERE art.[Action] = @action

	DELETE r
	FROM [dbo].[Results] r
	INNER JOIN [dev].[ActionResultTypes] art
	ON r.[ResultType] = art.[ResultType]
	WHERE art.[Action] = @action

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_DeleteAllResultsForMessageChoiceResultType]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_DeleteAllResultsForMessageChoiceResultType] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/16/2015
-- Description:	Deletes all Result records associated with all ResultTypes associated with the specified MessageChoice
-- =============================================
ALTER PROCEDURE [dev].[dev_DeleteAllResultsForMessageChoiceResultType]
	@messagechoice int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	DELETE rn
	FROM [dev].[ResultNames] rn
	INNER JOIN [dbo].[Results] r
	ON rn.[Result] = r.[Id]
	INNER JOIN [dev].[MessageChoiceResultTypes] mcrt
	ON r.[ResultType] = mcrt.[ResultType]
	WHERE mcrt.[MessageChoice] = @messagechoice

	DELETE r
	FROM [dbo].[Results] r
	INNER JOIN [dev].[MessageChoiceResultTypes] mcrt
	ON r.[ResultType] = mcrt.[ResultType]
	WHERE mcrt.[MessageChoice] = @messagechoice

END
GO

/******************************************************************************************************************************************/
/*Action***********************************************************************************************************************************/
/******************************************************************************************************************************************/

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_AddAction]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_AddAction] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/12/2015
-- Description:	Adds a Action record and returns the newly generated ID
-- =============================================
ALTER PROCEDURE [dev].[dev_AddAction]
	@verbtype int,
	@noun int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	INSERT INTO [dbo].[Actions] ([VerbType], [Noun])
	VALUES (@verbtype, @noun)
	
	SELECT SCOPE_IDENTITY()

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_UpdateAction]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_UpdateAction] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/12/2015
-- Description:	Updates a Action record
-- =============================================
ALTER PROCEDURE [dev].[dev_UpdateAction]
	@id int,
	@verbtype int,
	@noun int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	UPDATE [dbo].[Actions] 
	SET	[VerbType] = ISNULL(@verbtype, [VerbType]),
		[Noun] = ISNULL(@noun, [Noun])
	WHERE [Id] = @id

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_GetAllActionsForNoun]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_GetAllActionsForNoun] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/3/2015
-- Description:	Get all Action records associated with the specified Noun
-- =============================================
ALTER PROCEDURE [dev].[dev_GetAllActionsForNoun]
	@noun int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT a.[Id],
		   a.[VerbType],
		   a.[Noun],
		   an.[Name]
	FROM [dbo].[Actions] a
	INNER JOIN [dev].[ActionNames] an
	ON a.[Id] = an.[Action]
	WHERE a.[Noun] = @noun
	
	SELECT SCOPE_IDENTITY()

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_GetAction]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_GetAction] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/3/2015
-- Description:	Get an Action record in the database
-- =============================================
ALTER PROCEDURE [dev].[dev_GetAction]
	@id int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT a.[Id],
		   a.[VerbType],
		   a.[Noun],
		   an.[Name]
	FROM [dbo].[Actions] a
	INNER JOIN [dev].[ActionNames] an
	ON a.[Id] = an.[Action]
	WHERE a.[Id] = @id
	
	SELECT SCOPE_IDENTITY()

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_DeleteAllActionsForNoun]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_DeleteAllActionsForNoun] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/16/2015
-- Description:	Delete all Action records associated with the specified Noun
-- =============================================
ALTER PROCEDURE [dev].[dev_DeleteAllActionsForNoun]
	@noun int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;
	
	DELETE ar
	FROM [dbo].[ItemActionRequirements] ar
	INNER JOIN [dbo].[Actions] a
	ON ar.[Action] = a.[Id]
	WHERE a.[Noun] = @noun
	
	DELETE ar
	FROM [dbo].[EventActionRequirements] ar
	INNER JOIN [dbo].[Actions] a
	ON ar.[Action] = a.[Id]
	WHERE a.[Noun] = @noun
	
	DELETE ar
	FROM [dbo].[CharacterActionRequirements] ar
	INNER JOIN [dbo].[Actions] a
	ON ar.[Action] = a.[Id]
	WHERE a.[Noun] = @noun
	
	DELETE ar
	FROM [dbo].[ActionResults] ar
	INNER JOIN [dbo].[Actions] a
	ON ar.[Action] = a.[Id]
	WHERE a.[Noun] = @noun

	DELETE
	FROM [dbo].[Actions]
	WHERE [Noun] = @noun

END
GO

/******************************************************************************************************************************************/
/*ActionResult*****************************************************************************************************************************/
/******************************************************************************************************************************************/

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_AddActionResult]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_AddActionResult] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/4/2015
-- Description:	Adds a ActionResult record and returns the newly generated ID
-- =============================================
ALTER PROCEDURE [dev].[dev_AddActionResult]
	@result int,
	@action int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	INSERT INTO [dbo].[ActionResults] ([Result], [Action])
	VALUES (@result, @action)
	
	SELECT SCOPE_IDENTITY()

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_UpdateActionResult]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_UpdateActionResult] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/4/2015
-- Description:	Updates a ActionResult record
-- =============================================
ALTER PROCEDURE [dev].[dev_UpdateActionResult]
	@id int,
	@result int,
	@action int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	UPDATE [dbo].[ActionResults] 
	SET	[Result] = ISNULL(@result, [Result]),
		[Action] = ISNULL(@action, [Action])
	WHERE [Id] = @id

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_GetAllActionResultsForAction]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_GetAllActionResultsForAction] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/4/2015
-- Description:	Gets all ActionResult records associated with the specified Action
-- =============================================
ALTER PROCEDURE [dev].[dev_GetAllActionResultsForAction]
	@action int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [Id],
		   [Result],
		   [Action]
	FROM [dbo].[ActionResults]
	WHERE [Action] = @action

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_GetActionResult]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_GetActionResult] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/3/2015
-- Description:	Gets data about a ActionResult record in the database
-- =============================================
ALTER PROCEDURE [dev].[dev_GetActionResult]
	@id int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [Id],
		   [Result],
		   [Action]
	FROM [dbo].[ActionResults]
	WHERE [Id] = @id

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_DeleteAllActionResultsForAction]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_DeleteAllActionResultsForAction] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/16/2015
-- Description:	Deletes all ActionResult records associated with the specified Action
-- =============================================
ALTER PROCEDURE [dev].[dev_DeleteAllActionResultsForAction]
	@action int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	DELETE
	FROM [dbo].[ActionResults]
	WHERE [Action] = @action

END
GO

/******************************************************************************************************************************************/
/*Item*************************************************************************************************************************************/
/******************************************************************************************************************************************/

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_AddItem]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
  EXEC('CREATE PROCEDURE [dev].[dev_AddItem] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/12/2015
-- Description:	Adds an Item record and returns the newly generated ID
-- =============================================
ALTER PROCEDURE [dev].[dev_AddItem]
	@name varchar(500),
	@description varchar(MAX)
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	INSERT INTO [dbo].[Items] ([Name], [Description])
	VALUES (@name, @description)
	
	SELECT SCOPE_IDENTITY()

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_UpdateItem]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_UpdateItem] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/12/2015
-- Description:	Updates an Item record
-- =============================================
ALTER PROCEDURE [dev].[dev_UpdateItem]
	@id int,
	@name varchar(500),
	@description varchar(MAX)
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	UPDATE [dbo].[Items]
	SET [Name] = ISNULL(@name, [Name]),
		[Description] = ISNULL(@description, [Description])
	WHERE [Id] = @id

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_GetAllItems]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_GetAllItems] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/10/2015
-- Description:	Gets data about all Item records currently in the database
-- =============================================
ALTER PROCEDURE [dev].[dev_GetAllItems]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [Id],
		   [Name],
		   [Description]
	FROM [dbo].[Items]

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_GetItem]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_GetItem] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/10/2015
-- Description:	Gets data about an Item record from the database
-- =============================================
ALTER PROCEDURE [dev].[dev_GetItem]
	@id int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [Id],
		   [Name],
		   [Description]
	FROM [dbo].[Items]
	WHERE [Id] = @id

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_DeleteAllItems]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_DeleteAllItems] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/16/2015
-- Description:	Deletes data about all Item records currently in the database
-- =============================================
ALTER PROCEDURE [dev].[dev_DeleteAllItems]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;
	
	DELETE
	FROM [dbo].[ItemActionRequirements]

	DELETE
	FROM [dbo].[Items]
	
	DBCC CHECKIDENT ('[dbo].[ItemActionRequirements]', RESEED, 0)
	DBCC CHECKIDENT ('[dbo].[Items]', RESEED, 0)

END
GO

/******************************************************************************************************************************************/
/*Event************************************************************************************************************************************/
/******************************************************************************************************************************************/

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_AddEvent]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
  EXEC('CREATE PROCEDURE [dev].[dev_AddEvent] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/12/2015
-- Description:	Adds an Event record and returns the newly generated ID
-- =============================================
ALTER PROCEDURE [dev].[dev_AddEvent]
	@name varchar(500),
	@description varchar(MAX)
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	INSERT INTO [dbo].[Events] ([Name], [Description])
	VALUES (@name, @description)
	
	SELECT SCOPE_IDENTITY()

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_UpdateEvent]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_UpdateEvent] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/12/2015
-- Description:	Updates an Event record
-- =============================================
ALTER PROCEDURE [dev].[dev_UpdateEvent]
	@id int,
	@name varchar(500),
	@description varchar(MAX)
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	UPDATE [dbo].[Events]
	SET [Name] = ISNULL(@name, [Name]),
		[Description] = ISNULL(@description, [Description])
	WHERE [Id] = @id

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_GetAllEvents]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_GetAllEvents] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/10/2015
-- Description:	Gets data about all Event records currently in the database
-- =============================================
ALTER PROCEDURE [dev].[dev_GetAllEvents]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [Id],
		   [Name],
		   [Description]
	FROM [dbo].[Events]

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_GetEvent]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_GetEvent] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/10/2015
-- Description:	Gets data about an Event record from the database
-- =============================================
ALTER PROCEDURE [dev].[dev_GetEvent]
	@id int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [Id],
		   [Name],
		   [Description]
	FROM [dbo].[Events]
	WHERE [Id] = @id

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_DeleteAllEvents]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_DeleteAllEvents] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/16/2015
-- Description:	Deletes data about all Event records currently in the database
-- =============================================
ALTER PROCEDURE [dev].[dev_DeleteAllEvents]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	DELETE
	FROM [dbo].[EventActionRequirements]

	DELETE
	FROM [dbo].[Events]
	
	DBCC CHECKIDENT ('[dbo].[EventActionRequirements]', RESEED, 0)
	DBCC CHECKIDENT ('[dbo].[Events]', RESEED, 0)

END
GO

/******************************************************************************************************************************************/
/*Character********************************************************************************************************************************/
/******************************************************************************************************************************************/

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_AddCharacter]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
  EXEC('CREATE PROCEDURE [dev].[dev_AddCharacter] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/12/2015
-- Description:	Adds an Character record and returns the newly generated ID
-- =============================================
ALTER PROCEDURE [dev].[dev_AddCharacter]
	@name varchar(500),
	@description varchar(MAX)
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	INSERT INTO [dbo].[Characters] ([Name], [Description])
	VALUES (@name, @description)
	
	SELECT SCOPE_IDENTITY()

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_UpdateCharacter]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_UpdateCharacter] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/12/2015
-- Description:	Updates an Character record
-- =============================================
ALTER PROCEDURE [dev].[dev_UpdateCharacter]
	@id int,
	@name varchar(500),
	@description varchar(MAX)
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	UPDATE [dbo].[Characters]
	SET [Name] = ISNULL(@name, [Name]),
		[Description] = ISNULL(@description, [Description])
	WHERE [Id] = @id

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_GetAllCharacters]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_GetAllCharacters] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/10/2015
-- Description:	Gets data about all Character records currently in the database
-- =============================================
ALTER PROCEDURE [dev].[dev_GetAllCharacters]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [Id],
		   [Name],
		   [Description]
	FROM [dbo].[Characters]

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_GetCharacter]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_GetCharacter] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/10/2015
-- Description:	Gets data about an Character record from the database
-- =============================================
ALTER PROCEDURE [dev].[dev_GetCharacter]
	@id int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [Id],
		   [Name],
		   [Description]
	FROM [dbo].[Characters]
	WHERE [Id] = @id

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_DeleteAllCharacters]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_DeleteAllCharacters] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/16/2015
-- Description:	Deletes data about all Character records currently in the database
-- =============================================
ALTER PROCEDURE [dev].[dev_DeleteAllCharacters]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	DELETE
	FROM [dbo].[CharacterActionRequirements]

	DELETE
	FROM [dbo].[Characters]
	
	DBCC CHECKIDENT ('[dbo].[CharacterActionRequirements]', RESEED, 0)
	DBCC CHECKIDENT ('[dbo].[Characters]', RESEED, 0)

END
GO

/******************************************************************************************************************************************/
/*ItemActionRequirement********************************************************************************************************************/
/******************************************************************************************************************************************/

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_AddItemActionRequirement]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_AddItemActionRequirement] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/11/2015
-- Description:	Adds an ItemActionRequirement record and returns the newly generated ID
-- =============================================
ALTER PROCEDURE [dev].[dev_AddItemActionRequirement]
	@item int,
	@action int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra Requirement sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	INSERT INTO [dbo].[ItemActionRequirements] ([Item], [Action])
	VALUES (@item, @action)
	
	SELECT SCOPE_IDENTITY()

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_UpdateItemActionRequirement]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_UpdateItemActionRequirement] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/11/2015
-- Description:	Updates an ItemActionRequirement record
-- =============================================
ALTER PROCEDURE [dev].[dev_UpdateItemActionRequirement]
	@id int,
	@item int,
	@action int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra Requirement sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	UPDATE [dbo].[ItemActionRequirements] 
	SET	[Item] = ISNULL(@item, [Item]), 
		[Action] = ISNULL(@action, [Action])
	WHERE [Id] = @id

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_GetAllItemActionRequirementsForAction]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_GetAllItemActionRequirementsForAction] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/11/2015
-- Description:	Gets all ItemActionRequirements record for a specified Action
-- =============================================
ALTER PROCEDURE [dev].[dev_GetAllItemActionRequirementsForAction]
	@action int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra Requirement sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT ar.[Id],
		   ar.[Item],
		   i.[Name] as [ItemName],
		   ar.[Action],
		   an.[Name] as [ActionName]
	FROM [dbo].[ItemActionRequirements] ar
	INNER JOIN [dbo].[Items] i
	on ar.[Item] = i.[Id]
	INNER JOIN [dev].[ActionNames] an
	ON ar.[Action] = an.[Action]
	WHERE ar.[Action] = @action

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_GetItemActionRequirement]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_GetItemActionRequirement] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/11/2015
-- Description:	Gets an ItemActionRequirement record
-- =============================================
ALTER PROCEDURE [dev].[dev_GetItemActionRequirement]
	@id int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra Requirement sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT ar.[Id],
		   ar.[Item],
		   i.[Name] as [ItemName],
		   ar.[Action],
		   an.[Name] as [ActionName]
	FROM [dbo].[ItemActionRequirements] ar
	INNER JOIN [dbo].[Items] i
	on ar.[Item] = i.[Id]
	INNER JOIN [dev].[ActionNames] an
	ON ar.[Action] = an.[Action]
	WHERE ar.[Id] = @id

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_DeleteAllItemActionRequirementsForAction]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_DeleteAllItemActionRequirementsForAction] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/16/2015
-- Description:	Deletes all ItemActionRequirements record for a specified Action
-- =============================================
ALTER PROCEDURE [dev].[dev_DeleteAllItemActionRequirementsForAction]
	@action int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra Requirement sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	DELETE
	FROM [dbo].[ItemActionRequirements]
	WHERE [Action] = @action

END
GO

/******************************************************************************************************************************************/
/*EventActionRequirement*******************************************************************************************************************/
/******************************************************************************************************************************************/

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_AddEventActionRequirement]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_AddEventActionRequirement] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/11/2015
-- Description:	Adds an EventActionRequirement record and returns the newly generated ID
-- =============================================
ALTER PROCEDURE [dev].[dev_AddEventActionRequirement]
	@item int,
	@action int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra Requirement sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	INSERT INTO [dbo].[EventActionRequirements] ([Event], [Action])
	VALUES (@item, @action)
	
	SELECT SCOPE_IDENTITY()

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_UpdateEventActionRequirement]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_UpdateEventActionRequirement] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/11/2015
-- Description:	Updates an EventActionRequirement record
-- =============================================
ALTER PROCEDURE [dev].[dev_UpdateEventActionRequirement]
	@id int,
	@item int,
	@action int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra Requirement sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	UPDATE [dbo].[EventActionRequirements] 
	SET	[Event] = ISNULL(@item, [Event]), 
		[Action] = ISNULL(@action, [Action])
	WHERE [Id] = @id

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_GetAllEventActionRequirementsForAction]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_GetAllEventActionRequirementsForAction] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/11/2015
-- Description:	Gets all EventActionRequirements record for a specified Action
-- =============================================
ALTER PROCEDURE [dev].[dev_GetAllEventActionRequirementsForAction]
	@action int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra Requirement sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT ar.[Id],
		   ar.[Event],
		   i.[Name] as [EventName],
		   ar.[Action],
		   an.[Name] as [ActionName]
	FROM [dbo].[EventActionRequirements] ar
	INNER JOIN [dbo].[Events] i
	on ar.[Event] = i.[Id]
	INNER JOIN [dev].[ActionNames] an
	ON ar.[Action] = an.[Action]
	WHERE ar.[Action] = @action

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_GetEventActionRequirement]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_GetEventActionRequirement] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/11/2015
-- Description:	Gets an EventActionRequirement record
-- =============================================
ALTER PROCEDURE [dev].[dev_GetEventActionRequirement]
	@id int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra Requirement sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT ar.[Id],
		   ar.[Event],
		   i.[Name] as [EventName],
		   ar.[Action],
		   an.[Name] as [ActionName]
	FROM [dbo].[EventActionRequirements] ar
	INNER JOIN [dbo].[Events] i
	on ar.[Event] = i.[Id]
	INNER JOIN [dev].[ActionNames] an
	ON ar.[Action] = an.[Action]
	WHERE ar.[Id] = @id

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_DeleteAllEventActionRequirementsForAction]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_DeleteAllEventActionRequirementsForAction] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/16/2015
-- Description:	Deletes all EventActionRequirements record for a specified Action
-- =============================================
ALTER PROCEDURE [dev].[dev_DeleteAllEventActionRequirementsForAction]
	@action int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra Requirement sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	DELETE
	FROM [dbo].[EventActionRequirements]
	WHERE [Action] = @action

END
GO

/******************************************************************************************************************************************/
/*CharacterActionRequirement***************************************************************************************************************/
/******************************************************************************************************************************************/

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_AddCharacterActionRequirement]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_AddCharacterActionRequirement] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/11/2015
-- Description:	Adds an CharacterActionRequirement record and returns the newly generated ID
-- =============================================
ALTER PROCEDURE [dev].[dev_AddCharacterActionRequirement]
	@item int,
	@action int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra Requirement sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	INSERT INTO [dbo].[CharacterActionRequirements] ([Character], [Action])
	VALUES (@item, @action)
	
	SELECT SCOPE_IDENTITY()

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_UpdateCharacterActionRequirement]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_UpdateCharacterActionRequirement] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/11/2015
-- Description:	Updates an CharacterActionRequirement record
-- =============================================
ALTER PROCEDURE [dev].[dev_UpdateCharacterActionRequirement]
	@id int,
	@item int,
	@action int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra Requirement sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	UPDATE [dbo].[CharacterActionRequirements] 
	SET	[Character] = ISNULL(@item, [Character]), 
		[Action] = ISNULL(@action, [Action])
	WHERE [Id] = @id

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_GetAllCharacterActionRequirementsForAction]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_GetAllCharacterActionRequirementsForAction] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/11/2015
-- Description:	Gets all CharacterActionRequirements record for a specified Action
-- =============================================
ALTER PROCEDURE [dev].[dev_GetAllCharacterActionRequirementsForAction]
	@action int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra Requirement sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT ar.[Id],
		   ar.[Character],
		   i.[Name] as [CharacterName],
		   ar.[Action],
		   an.[Name] as [ActionName]
	FROM [dbo].[CharacterActionRequirements] ar
	INNER JOIN [dbo].[Characters] i
	on ar.[Character] = i.[Id]
	INNER JOIN [dev].[ActionNames] an
	ON ar.[Action] = an.[Action]
	WHERE ar.[Action] = @action

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_GetCharacterActionRequirement]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_GetCharacterActionRequirement] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/11/2015
-- Description:	Gets an CharacterActionRequirement record
-- =============================================
ALTER PROCEDURE [dev].[dev_GetCharacterActionRequirement]
	@id int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra Requirement sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT ar.[Id],
		   ar.[Character],
		   i.[Name] as [CharacterName],
		   ar.[Action],
		   an.[Name] as [ActionName]
	FROM [dbo].[CharacterActionRequirements] ar
	INNER JOIN [dbo].[Characters] i
	on ar.[Character] = i.[Id]
	INNER JOIN [dev].[ActionNames] an
	ON ar.[Action] = an.[Action]
	WHERE ar.[Id] = @id

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_DeleteAllCharacterActionRequirementsForAction]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_DeleteAllCharacterActionRequirementsForAction] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/16/2015
-- Description:	Deletes all CharacterActionRequirements record for a specified Action
-- =============================================
ALTER PROCEDURE [dev].[dev_DeleteAllCharacterActionRequirementsForAction]
	@action int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra Requirement sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	DELETE
	FROM [dbo].[CharacterActionRequirements]
	WHERE [Action] = @action

END
GO

/******************************************************************************************************************************************/
/*Message**********************************************************************************************************************************/
/******************************************************************************************************************************************/

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_AddMessage]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
  EXEC('CREATE PROCEDURE [dev].[dev_AddMessage] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/12/2015
-- Description:	Adds an Message record and returns the newly generated ID
-- =============================================
ALTER PROCEDURE [dev].[dev_AddMessage]
	@name varchar(500),
	@text varchar(MAX)
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	DECLARE @messageid decimal

	INSERT INTO [dbo].[Messages] ([Text])
	VALUES (@text)
	
	SELECT @messageid = SCOPE_IDENTITY()
	
	INSERT INTO [dev].[MessageNames] ([Message], [Name])
	VALUES (@messageid, @name)
	
	SELECT @messageid

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_UpdateMessage]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_UpdateMessage] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/12/2015
-- Description:	Updates an Message record
-- =============================================
ALTER PROCEDURE [dev].[dev_UpdateMessage]
	@id int,
	@name varchar(500),
	@text varchar(MAX)
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	UPDATE [dbo].[Messages]
	SET [Text] = ISNULL(@text, [Text])
	WHERE [Id] = @id
	
	UPDATE [dev].[MessageNames]
	SET [Name] = ISNULL(@name, [Name])
	WHERE [Message] = @id

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_GetAllMessages]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_GetAllMessages] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/12/2015
-- Description:	Gets all Message records from the database
-- =============================================
ALTER PROCEDURE [dev].[dev_GetAllMessages]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT m.[Id],
		   mn.[Name],
		   m.[Text]
	FROM [dbo].[Messages] m
	INNER JOIN [dev].[MessageNames] mn
	ON mn.[Message] = m.[Id]

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_GetMessage]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_GetMessage] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/12/2015
-- Description:	Gets a Message record
-- =============================================
ALTER PROCEDURE [dev].[dev_GetMessage]
	@id int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT m.[Id],
		   mn.[Name],
		   m.[Text]
	FROM [dbo].[Messages] m
	INNER JOIN [dev].[MessageNames] mn
	ON mn.[Message] = m.[Id]
	WHERE m.[Id] = @id

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_DeleteAllMessages]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_DeleteAllMessages] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/16/2015
-- Description:	Deletes all Message records from the database
-- =============================================
ALTER PROCEDURE [dev].[dev_DeleteAllMessages]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;
	
	DELETE
	FROM [dbo].[MessageChoiceResults]
	
	DELETE
	FROM [dev].[MessageChoiceNames]

	DELETE
	FROM [dbo].[MessageChoices]
	
	DELETE
	FROM [dev].[MessageNames]

	DELETE
	FROM [dbo].[Messages]
	
	DBCC CHECKIDENT ('[dbo].[MessageChoiceResults]', RESEED, 0)
	DBCC CHECKIDENT ('[dbo].[MessageChoices]', RESEED, 0)
	DBCC CHECKIDENT ('[dbo].[Messages]', RESEED, 0)

END
GO

/******************************************************************************************************************************************/
/*MessageChoice****************************************************************************************************************************/
/******************************************************************************************************************************************/

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_AddMessageChoice]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
  EXEC('CREATE PROCEDURE [dev].[dev_AddMessageChoice] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/12/2015
-- Description:	Adds an MessageChoice record and returns the newly generated ID
-- =============================================
ALTER PROCEDURE [dev].[dev_AddMessageChoice]
	@name varchar(500),
	@text varchar(MAX),
	@message int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	DECLARE @messageid decimal

	INSERT INTO [dbo].[MessageChoices] ([Text], [Message])
	VALUES (@text, @message)
	
	SELECT @messageid = SCOPE_IDENTITY()
	
	INSERT INTO [dev].[MessageChoiceNames] ([MessageChoice], [Name])
	VALUES (@messageid, @name)
	
	SELECT @messageid

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_UpdateMessageChoice]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_UpdateMessageChoice] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/12/2015
-- Description:	Updates an MessageChoice record
-- =============================================
ALTER PROCEDURE [dev].[dev_UpdateMessageChoice]
	@id int,
	@name varchar(500),
	@text varchar(MAX),
	@message int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	UPDATE [dbo].[MessageChoices]
	SET [Text] = ISNULL(@text, [Text]),
		[Message] = ISNULL(@message, [Message])
	WHERE [Id] = @id
	
	UPDATE [dev].[MessageChoiceNames]
	SET [Name] = ISNULL(@name, [Name])
	WHERE [MessageChoice] = @id

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_GetAllMessageChoicesForMessage]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_GetAllMessageChoicesForMessage] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/12/2015
-- Description:	Gets all MessageChoice records from the database
-- =============================================
ALTER PROCEDURE [dev].[dev_GetAllMessageChoicesForMessage]
	@message int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT m.[Id],
		   mn.[Name],
		   m.[Text],
		   m.[Message]
	FROM [dbo].[MessageChoices] m
	INNER JOIN [dev].[MessageChoiceNames] mn
	ON mn.[MessageChoice] = m.[Id]
	WHERE m.[Message] = @message

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_GetMessageChoice]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_GetMessageChoice] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/12/2015
-- Description:	Gets a MessageChoice record
-- =============================================
ALTER PROCEDURE [dev].[dev_GetMessageChoice]
	@id int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT m.[Id],
		   mn.[Name],
		   m.[Text],
		   m.[Message]
	FROM [dbo].[MessageChoices] m
	INNER JOIN [dev].[MessageChoiceNames] mn
	ON mn.[MessageChoice] = m.[Id]
	WHERE m.[Id] = @id

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_DeleteAllMessageChoicesForMessage]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_DeleteAllMessageChoicesForMessage] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/16/2015
-- Description:	Deletes all MessageChoice records associated with the specified Message
-- =============================================
ALTER PROCEDURE [dev].[dev_DeleteAllMessageChoicesForMessage]
	@message int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;
	
	DELETE mcr
	FROM [dbo].[MessageChoiceResults] mcr
	INNER JOIN [dbo].[MessageChoices] mc
	ON mcr.[MessageChoice] = mc.[Id]
	WHERE mc.[Message] = @message
	
	DELETE mcn
	FROM [dev].[MessageChoiceNames] mcn
	INNER JOIN [dbo].[MessageChoices] mc
	ON mcn.[MessageChoice] = mc.[Id]
	WHERE mc.[Message] = @message

	DELETE
	FROM [dbo].[MessageChoices]
	WHERE [Message] = @message

END
GO

/******************************************************************************************************************************************/
/*MessageChoiceResult*********************************************************************************************************************/
/******************************************************************************************************************************************/

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_AddMessageChoiceResult]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
  EXEC('CREATE PROCEDURE [dev].[dev_AddMessageChoiceResult] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/12/2015
-- Description:	Adds an MessageChoiceResult record and returns the newly generated ID
-- =============================================
ALTER PROCEDURE [dev].[dev_AddMessageChoiceResult]
	@result int,
	@messagechoice int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	INSERT INTO [dbo].[MessageChoiceResults] ([Result], [MessageChoice])
	VALUES (@result, @messagechoice)
	
	SELECT SCOPE_IDENTITY()

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_UpdateMessageChoiceResult]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_UpdateMessageChoiceResult] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/12/2015
-- Description:	Updates an MessageChoiceResult record
-- =============================================
ALTER PROCEDURE [dev].[dev_UpdateMessageChoiceResult]
	@id int,
	@result int,
	@messagechoice int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	UPDATE [dbo].[MessageChoiceResults]
	SET [Result] = ISNULL(@result, [Result]),
		[MessageChoice] = ISNULL(@messagechoice, [MessageChoice])
	WHERE [Id] = @id

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_GetAllMessageChoiceResultsForMessageChoice]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_GetAllMessageChoiceResultsForMessageChoice] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/13/2015
-- Description:	Gets all MessageChoiceResult records associated with the specified MessageChoice
-- =============================================
ALTER PROCEDURE [dev].[dev_GetAllMessageChoiceResultsForMessageChoice]
	@messagechoice int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [Id],
		   [Result],
		   [MessageChoice]
	FROM [dbo].[MessageChoiceResults]
	WHERE [MessageChoice] = @messagechoice

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_GetMessageChoiceResult]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_GetMessageChoiceResult] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/13/2015
-- Description:	Gets data about a MessageChoiceResult record in the database
-- =============================================
ALTER PROCEDURE [dev].[dev_GetMessageChoiceResult]
	@id int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [Id],
		   [Result],
		   [MessageChoice]
	FROM [dbo].[MessageChoiceResults]
	WHERE [Id] = @id

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_DeleteAllMessageChoiceResultsForMessageChoice]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_DeleteAllMessageChoiceResultsForMessageChoice] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/16/2015
-- Description:	Deletes all MessageChoiceResult records associated with the specified MessageChoice
-- =============================================
ALTER PROCEDURE [dev].[dev_DeleteAllMessageChoiceResultsForMessageChoice]
	@messagechoice int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	DELETE
	FROM [dbo].[MessageChoiceResults]
	WHERE [MessageChoice] = @messagechoice

END
GO

/******************************************************************************************************************************************/
/*PlayerInventory**************************************************************************************************************************/
/******************************************************************************************************************************************/

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_AddPlayerInventory]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
  EXEC('CREATE PROCEDURE [dev].[dev_AddPlayerInventory] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/12/2015
-- Description:	Adds an PlayerInventory record and returns the newly generated ID
-- =============================================
ALTER PROCEDURE [dev].[dev_AddPlayerInventory]
	@player uniqueidentifier,
	@item int,
	@active bit
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	INSERT INTO [dbo].[PlayerInventory] ([Player], [Item], [Active])
	VALUES (@player, @item, @active)
	
	SELECT SCOPE_IDENTITY()

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_UpdatePlayerInventory]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_UpdatePlayerInventory] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/12/2015
-- Description:	Updates an PlayerInventory record
-- =============================================
ALTER PROCEDURE [dev].[dev_UpdatePlayerInventory]
	@player uniqueidentifier,
	@item int,
	@active bit
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	UPDATE [dbo].[PlayerInventory]
	SET [Active] = ISNULL(@active, [Active])
	WHERE [Player] = @player AND [Item] = @item

END
GO

/******************************************************************************************************************************************/
/*PlayerHistory****************************************************************************************************************************/
/******************************************************************************************************************************************/

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_AddPlayerHistory]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
  EXEC('CREATE PROCEDURE [dev].[dev_AddPlayerHistory] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/12/2015
-- Description:	Adds an PlayerHistory record and returns the newly generated ID
-- =============================================
ALTER PROCEDURE [dev].[dev_AddPlayerHistory]
	@player uniqueidentifier,
	@event int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	INSERT INTO [dbo].[PlayerHistory] ([Player], [Event])
	VALUES (@player, @event)
	
	SELECT SCOPE_IDENTITY()

END
GO

/******************************************************************************************************************************************/
/*PlayerParty******************************************************************************************************************************/
/******************************************************************************************************************************************/

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_AddPlayerParty]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
  EXEC('CREATE PROCEDURE [dev].[dev_AddPlayerParty] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/12/2015
-- Description:	Adds an PlayerParty record and returns the newly generated ID
-- =============================================
ALTER PROCEDURE [dev].[dev_AddPlayerParty]
	@player uniqueidentifier,
	@Character int,
	@active bit
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	INSERT INTO [dbo].[PlayerParty] ([Player], [Character], [Active])
	VALUES (@player, @Character, @active)
	
	SELECT SCOPE_IDENTITY()

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_UpdatePlayerParty]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_UpdatePlayerParty] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/12/2015
-- Description:	Updates an PlayerParty record
-- =============================================
ALTER PROCEDURE [dev].[dev_UpdatePlayerParty]
	@player uniqueidentifier,
	@Character int,
	@active bit
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	UPDATE [dbo].[PlayerParty]
	SET [Active] = ISNULL(@active, [Active])
	WHERE [Player] = @player AND [Character] = @Character

END
GO

/******************************************************************************************************************************************/
/*Player***********************************************************************************************************************************/
/******************************************************************************************************************************************/

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_AddPlayer]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
  EXEC('CREATE PROCEDURE [dev].[dev_AddPlayer] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/12/2015
-- Description:	Adds an Player record and returns the newly generated ID
-- =============================================
ALTER PROCEDURE [dev].[dev_AddPlayer]
	@username varchar(max),
	@domainname varchar(max),
	@domain varchar(max),
	@password varchar(max)
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	DECLARE @usernameid int
	DECLARE @domainnameid int
	DECLARE @domainid int
	DECLARE @playerid uniqueidentifier

	-- Insert the UserName, get the new Id
	INSERT INTO [dbo].[EmailUserNames] ([UserName])
	VALUES (@username)
	
	SELECT @usernameid = SCOPE_IDENTITY()
	
	-- Check to see if the DomainName is already there and, if not, create it
	SELECT @domainnameid = [Id] FROM [dbo].[EmailDomainNames] WHERE [DomainName] = @domainname
	
	IF (@domainnameid IS NULL)
	BEGIN
		INSERT INTO [dbo].[EmailDomainNames] ([DomainName])
		VALUES (@domainname)
		
		SELECT @domainnameid = SCOPE_IDENTITY()		
	END
	
	-- Check to see if the Domain is already there and, if not, create it
	SELECT @domainid = [Id] FROM [dbo].[EmailDomains] WHERE [Domain] = @domain
	
	IF (@domainid IS NULL)
	BEGIN
		INSERT INTO [dbo].[EmailDomains] ([Domain])
		VALUES (@domain)
		
		SELECT @domainid = SCOPE_IDENTITY()		
	END
	
	-- Insert player	
	SELECT @playerid = NEWID()
	
	INSERT INTO [dbo].[Player] ([EmailUserName], [EmailDomainName], [EmailDomain], [Password], [Id])
	VALUES (@usernameid, @domainnameid, @domainid, @password, @playerid)
	
	SELECT @playerid

END
GO