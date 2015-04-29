CREATE TABLE [dbo].[Nouns]
(
	[Id] INT NOT NULL PRIMARY KEY IDENTITY, 
    [Name] VARCHAR(MAX) NOT NULL,

)

GO

CREATE INDEX [IX_Nouns_Id] ON [dbo].[Nouns] ([Id])
