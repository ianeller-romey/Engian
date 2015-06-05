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

/******************************************************************************************************************************************/
/*ResultTypeJSONField**********************************************************************************************************************/
/******************************************************************************************************************************************/

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_AddResultTypeJSONField]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_AddResultTypeJSONField] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/4/2015
-- Description:	Adds a ResultTypeJSONField record and returns the newly generated ID
-- =============================================
ALTER PROCEDURE [dev].[dev_AddResultTypeJSONField]
	@jsonfield varchar(MAX),
	@resulttype int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	INSERT INTO [dev].[ResultTypeJSONFields] ([JSONField], [ResultType])
	VALUES (@jsonfield, @resulttype)
	
	SELECT SCOPE_IDENTITY()

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_UpdateResultTypeJSONField]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_UpdateResultTypeJSONField] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/4/2015
-- Description:	Updates a ResultTypeJSONField record
-- =============================================
ALTER PROCEDURE [dev].[dev_UpdateResultTypeJSONField]
	@id int,
	@jsonfield varchar(MAX),
	@resulttype int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	UPDATE [dev].[ResultTypeJSONFields] 
	SET	[JSONField] = ISNULL(@jsonfield, [JSONField]),
		[ResultType] = ISNULL(@resulttype, [ResultType])
	WHERE [Id] = @id

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_GetAllResultTypeJSONFieldsForResultType]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_GetAllResultTypeJSONFieldsForResultType] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/4/2015
-- Description:	Gets the all ResultTypeJSONFields records associated with the specified ResultType
-- =============================================
ALTER PROCEDURE [dev].[dev_GetAllResultTypeJSONFieldsForResultType]
	@resulttype int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [Id],
		   [JSONField],
		   [ResultType]
	FROM [dev].[ResultTypeJSONFields]
	WHERE [ResultType] = @resulttype

END
GO

IF NOT EXISTS (SELECT 1 FROM [dbo].[sysobjects] WHERE [id] = object_id(N'[dev].[dev_GetResultTypeJSONField]') AND OBJECTPROPERTY([id], N'IsProcedure') = 1)
	EXEC('CREATE PROCEDURE [dev].[dev_GetResultTypeJSONField] AS SELECT 1')
GO
-- =============================================
-- Author:		Ian Eller-Romey
-- Create date: 6/4/2015
-- Description:	Gets data about a ResultTypeJSONField record in the database
-- =============================================
ALTER PROCEDURE [dev].[dev_GetResultTypeJSONField]
	@id int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [Id],
		   [JSONField],
		   [ResultType]
	FROM [dev].[ResultTypeJSONFields]
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

	INSERT INTO [dbo].[Results] ([Name], [JSONData], [ResultType])
	VALUES (@name, @jsondata, @resulttype)
	
	SELECT SCOPE_IDENTITY()

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
	SET	[Name] = ISNULL(@name, [Name]),
		[JSONData] = @jsondata, 
		[ResultType] = ISNULL(@resulttype, [ResultType])
	WHERE [Id] = @id

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
	FROM [dbo].[Results]
	WHERE [ResultType] = @resulttype

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
	FROM [dbo].[Results]
	WHERE [Id] = @id
	
	SELECT SCOPE_IDENTITY()

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

	SELECT [Id],
		   [VerbType],
		   [Noun]
	FROM [dbo].[Actions]
	WHERE [Noun] = @noun
	
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

	SELECT [Id],
		   [VerbType],
		   [Noun]
	FROM [dbo].[Actions]
	WHERE [Id] = @id
	
	SELECT SCOPE_IDENTITY()

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
	@requirement int,
	@requirementsourcetype int,
	@action int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra Requirement sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	INSERT INTO [dbo].[Requirements] ([Requirement], [RequirementSourceType], [Action])
	VALUES (@requirement, @requirementsourcetype, @action)
	
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
	@requirement int,
	@requirementsourcetype int,
	@action int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra Requirement sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	UPDATE [dbo].[Requirements] 
	SET	[Requirement] = ISNULL(@requirement, [Requirement]), 
		[RequirementSourceType] = ISNULL(@requirementsourcetype, [RequirementSourceType]),
		[Action] = ISNULL(@action, [Action])
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
	@text varchar(MAX),
	@message int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	INSERT INTO [dbo].[MessageChoices] ([Text], [Message])
	VALUES (@text, @message)
	
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