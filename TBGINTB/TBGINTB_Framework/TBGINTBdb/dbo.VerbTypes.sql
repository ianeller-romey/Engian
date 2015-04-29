CREATE TABLE [dbo].[VerbTypes]
(
	[Id] INT NOT NULL PRIMARY KEY IDENTITY, 
    [Type] VARCHAR(50) NOT NULL,
)

GO

CREATE INDEX [IX_VerbTypes_Id] ON [dbo].[VerbTypes] ([Id])
