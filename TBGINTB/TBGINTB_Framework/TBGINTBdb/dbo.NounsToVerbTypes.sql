CREATE TABLE [dbo].[NounsToVerbTypes]
(
	[Noun] INT NOT NULL, 
    [VerbType] INT NOT NULL, 
    CONSTRAINT [FK_NounsToVerbTypes_Nouns] FOREIGN KEY ([Noun]) REFERENCES [Nouns]([Id]), 
    CONSTRAINT [FK_NounsToVerbTypes_VerbTypes] FOREIGN KEY ([VerbType]) REFERENCES [VerbTypes]([Id]) 
)

GO

CREATE INDEX [IX_NounsToVerbTypes_Noun] ON [dbo].[NounsToVerbTypes] ([Noun])

GO

CREATE INDEX [IX_NounsToVerbTypes_VerbType] ON [dbo].[NounsToVerbTypes] ([VerbType])
