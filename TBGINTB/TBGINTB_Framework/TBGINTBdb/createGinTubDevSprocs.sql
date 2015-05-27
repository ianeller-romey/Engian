USE [GinTub]

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
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
		   ISNULL(MAX(r.[X]), 0) as [MaxX],
		   ISNULL(MIN(r.[X]), 0) as [MinX],
		   ISNULL(MAX(r.[Y]), 0) as [MaxY],
		   ISNULL(MIN(r.[Y]), 0) as [MinY],
		   ISNULL(MAX(r.[Z]), 0) as [MaxZ],
		   ISNULL(MIN(r.[Z]), 0) as [MinZ],
		   COUNT(r.[Id]) as [NumRooms]
	FROM [dbo].[Areas] a
	LEFT JOIN [dbo].[Rooms] r
	ON r.[Area] = a.[Id]
	WHERE a.[Id] = @id
	GROUP BY a.[Id], a.[Name]

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
	
	DELETE FROM [dbo].[Areas]

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
	@room int,
	@location int,
	@time datetime
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

    DECLARE @newstate int
    SELECT @newstate = ISNULL(MAX([State]), -1) + 1
    FROM [dbo].[RoomStates]
    WHERE [Room] = @room
    
	INSERT INTO [dbo].[RoomStates] ([Room], [State], [Location], [Time])
	VALUES (@room, @newstate, @location, @time)
	
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
	@room int,
	@state int,
	@location int,
	@time datetime
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	UPDATE [dbo].[RoomStates] 
	SET	[Room] = ISNULL(@room, [Room]),
		[State] = ISNULL(@state, [State]),
		[Location] = ISNULL(@location, [Location]), 
		[Time] = @time
	WHERE	[Id] = @id

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
		   [Room],
		   [State],
		   [Location],
		   [Time]
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
		   [Room],
		   [State],
		   [Location],
		   [Time]
	FROM [dbo].[RoomStates]
	WHERE [Id] = @id

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
-- Description:	Adds a Paragraph record and returns the newly generated ID, OR adds a new state to an existing Paragraph record
-- =============================================
ALTER PROCEDURE [dev].[dev_AddParagraph]
	@id int,
	@text varchar(MAX),
	@room int,
	@roomstate int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

    DECLARE @newstate int
    SELECT @newstate = ISNULL(MAX([State]), -1) + 1
    FROM [dbo].[Paragraphs]
    WHERE [Room] = @room
    AND [RoomState] = @roomState
    AND [Id] = @id
    
    IF @id IS NULL
    BEGIN
		INSERT INTO [dbo].[Paragraphs] ([Text], [Room], [RoomState], [State])
		VALUES (@text, @room, @roomstate, @newstate)
	END
	ELSE
	BEGIN
		SET IDENTITY_INSERT [dbo].[Paragraphs] ON
		
		INSERT INTO [dbo].[Paragraphs] ([Id], [Text], [Room], [RoomState], [State])
		VALUES (@id, @text, @room, @roomstate, @newstate)
		
		SET IDENTITY_INSERT [dbo].[Paragraphs] ON
	END
	
	SELECT SCOPE_IDENTITY() as [Id], @newstate as [State]

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
	@text varchar(MAX),
	@room int,
	@roomstate int,
	@state int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	UPDATE [dbo].[Paragraphs] 
	SET	[Text] = ISNULL(@text, [Text]), 
		[Room] = ISNULL(@room, [Room]),
		[RoomState] = @roomState
	WHERE [Id] = @id AND [State] = @state

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
		   [Text],
		   [Room],
		   [RoomState],
		   [State]
	FROM [dbo].[Paragraphs]
	WHERE [Room] = @room
	AND ([RoomState] = @roomstate OR @roomstate IS NULL)

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
	@id int,
	@state int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [Id],
		   [Text],
		   [Room],
		   [RoomState],
		   [State]
	FROM [dbo].[Paragraphs]
	WHERE [Id] = @id
	AND [State] = @state

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
-- Description:	Adds a Noun record, checking to ensure that the specified text value IS present in the Paragraph, 
-- and returns the newly generated ID
-- =============================================
ALTER PROCEDURE [dev].[dev_AddNoun]
	@text varchar(MAX),
	@paragraph int,
	@paragraphstate int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;
	
	IF NOT EXISTS (SELECT 1
				   FROM [dbo].[Paragraphs] p
				   WHERE [Id] = @paragraph AND [State] = @paragraphstate AND [Text] LIKE '%' + @text + '%')
	BEGIN
		RAISERROR (N'The Text value of a Noun must be present in the Text value of the Paragraph to which it is associated.',
				   1,
				   1)
	END

	INSERT INTO [dbo].[Nouns] ([Text], [Paragraph], [ParagraphState])
	VALUES (@text, @paragraph, @paragraphstate)
	
	SELECT SCOPE_IDENTITY()

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
	@noun int,
	@verbtype int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	INSERT INTO [dbo].[Actions] ([Noun], [VerbType])
	VALUES (@noun, @verbtype)
	
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
	@noun int,
	@verbtype int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	UPDATE [dbo].[Actions] 
	SET	[Noun] = ISNULL(@noun, [Noun]),
		[VerbType] = ISNULL(@verbtype, [VerbType])
	WHERE [Id] = @id

END
GO

/******************************************************************************************************************************************/
/*ResultSourceType*************************************************************************************************************************/
/******************************************************************************************************************************************/

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_AddResultSourceType]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_AddResultSourceType] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/12/2015
-- Description:	Adds a ResultSourceType record and returns the newly generated ID
-- =============================================
ALTER PROCEDURE [dev].[dev_AddResultSourceType]
	@name varchar(500)
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	INSERT INTO [dbo].[ResultSourceTypes] ([Name])
	VALUES (@name)
	
	SELECT SCOPE_IDENTITY()

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_UpdateResultSourceType]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_UpdateResultSourceType] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/12/2015
-- Description:	Updates a ResultSourceType record
-- =============================================
ALTER PROCEDURE [dev].[dev_UpdateResultSourceType]
	@id int,
	@name varchar(500)
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	UPDATE [dbo].[ResultSourceTypes] 
	SET	[Name] = ISNULL(@name, [Name])
	WHERE [Id] = @id

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

/******************************************************************************************************************************************/
/*Result***********************************************************************************************************************************/
/******************************************************************************************************************************************/

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_AddResult]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_AddResult] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/12/2015
-- Description:	Adds a Result record and returns the newly generated ID
-- =============================================
ALTER PROCEDURE [dev].[dev_AddResult]
	@resulttype int,
	@resultsourcetype int,
	@source int,
	@jsondata varchar(MAX)
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	INSERT INTO [dbo].[Results] ([ResultType], [ResultSourceType], [Source], [JSONData])
	VALUES (@resulttype, @resultsourcetype, @source, @jsondata)
	
	SELECT SCOPE_IDENTITY()

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_UpdateResult]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_UpdateResult] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/12/2015
-- Description:	Updates a Result record
-- =============================================
ALTER PROCEDURE [dev].[dev_UpdateResult]
	@id int,
	@resulttype int,
	@resultsourcetype int,
	@source int,
	@jsondata varchar(MAX)
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	UPDATE [dbo].[Results] 
	SET	[ResultType] = ISNULL(@resulttype, [ResultType]), 
		[ResultSourceType] = ISNULL(@resultsourcetype, [ResultSourceType]), 
		[Source] = ISNULL(@source, [Source]), 
		[JSONData] = ISNULL(@jsondata, [JSONData])
	WHERE [Id] = @id

END
GO

/******************************************************************************************************************************************/
/*RequirementSourceType********************************************************************************************************************/
/******************************************************************************************************************************************/

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_AddRequirementSourceType]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_AddRequirementSourceType] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/12/2015
-- Description:	Adds a RequirementSourceType record and returns the newly generated ID
-- =============================================
ALTER PROCEDURE [dev].[dev_AddRequirementSourceType]
	@name varchar(500)
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra Requirement sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	INSERT INTO [dbo].[RequirementSourceTypes] ([Name])
	VALUES (@name)
	
	SELECT SCOPE_IDENTITY()

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_UpdateRequirementSourceType]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_UpdateRequirementSourceType] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/12/2015
-- Description:	Updates a RequirementSourceType record
-- =============================================
ALTER PROCEDURE [dev].[dev_UpdateRequirementSourceType]
	@id int,
	@name varchar(500)
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra Requirement sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	UPDATE [dbo].[RequirementSourceTypes] 
	SET	[Name] = ISNULL(@name, [Name])
	WHERE [Id] = @id

END
GO

/******************************************************************************************************************************************/
/*Requirement******************************************************************************************************************************/
/******************************************************************************************************************************************/

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_AddRequirement]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_AddRequirement] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/12/2015
-- Description:	Adds a Requirement record and returns the newly generated ID; remember that the @requirement parameter
-- corresponds to the ID of an item, event, or character depending on the @requirementsourcetype
-- =============================================
ALTER PROCEDURE [dev].[dev_AddRequirement]
	@action int,
	@requirementsourcetype int,
	@requirement int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra Requirement sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	INSERT INTO [dbo].[Requirements] ([Action], [RequirementSourceType], [Requirement])
	VALUES (@action, @requirementsourcetype, @requirement)
	
	SELECT SCOPE_IDENTITY()

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_UpdateRequirement]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_UpdateRequirement] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/12/2015
-- Description:	Updates a Requirement record; remember that the @requirement parameter
-- corresponds to the ID of an item, event, or character depending on the @requirementsourcetype
-- =============================================
ALTER PROCEDURE [dev].[dev_UpdateRequirement]
	@id int,
	@action int,
	@requirementsourcetype int,
	@requirement int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra Requirement sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	UPDATE [dbo].[Requirements] 
	SET	[Action] = ISNULL(@action, [Action]), 
		[RequirementSourceType] = ISNULL(@requirementsourcetype, [RequirementSourceType]), 
		[Requirement] = ISNULL(@requirement, [Requirement])
	WHERE [Id] = @id

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
	@text varchar(MAX)
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	INSERT INTO [dbo].[Messages] ([Text])
	VALUES (@text)
	
	SELECT SCOPE_IDENTITY()

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
	@text varchar(MAX)
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	UPDATE [dbo].[Messages]
	SET [Text] = ISNULL(@text, [Text])
	WHERE [Id] = @id

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
	@message int,
	@text varchar(MAX)
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	INSERT INTO [dbo].[MessageChoices] ([Message], [Text])
	VALUES (@message, @text)
	
	SELECT SCOPE_IDENTITY()

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
	@text varchar(MAX)
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	UPDATE [dbo].[MessageChoices]
	SET [Text] = ISNULL(@text, [Text])
	WHERE [Id] = @id

END
GO

/******************************************************************************************************************************************/
/*MessageChoiceOutcome*********************************************************************************************************************/
/******************************************************************************************************************************************/

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_AddMessageChoiceOutcome]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
  EXEC('CREATE PROCEDURE [dev].[dev_AddMessageChoiceOutcome] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/12/2015
-- Description:	Adds an MessageChoiceOutcome record and returns the newly generated ID
-- =============================================
ALTER PROCEDURE [dev].[dev_AddMessageChoiceOutcome]
	@messagechoice int,
	@result int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	INSERT INTO [dbo].[MessageChoiceOutcomes] ([MessageChoice], [Result])
	VALUES (@messagechoice, @result)
	
	SELECT SCOPE_IDENTITY()

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_UpdateMessageChoiceOutcome]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_UpdateMessageChoiceOutcome] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 5/12/2015
-- Description:	Updates an MessageChoiceOutcome record
-- =============================================
ALTER PROCEDURE [dev].[dev_UpdateMessageChoiceOutcome]
	@id int,
	@result int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	UPDATE [dbo].[MessageChoiceOutcomes]
	SET [Result] = @result
	WHERE [Id] = @id

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

/******************************************************************************************************************************************/
/*PlayerHistory****************************************************************************************************************************/
/******************************************************************************************************************************************/

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