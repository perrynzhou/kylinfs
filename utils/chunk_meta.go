package utils

type ChunkServer struct {
	Id          string
	ChunkAddr   string
	ChunkPort   string
	BlockMbSize int
	TotalMbSize uint64
	FreeMbSize  uint64
}

type ChunkMeta struct {
	Id         uint64
	BlkSize    uint64
	DelSize    uint64
	DelMap     map[uint64]uint64
	InodeCount uint64
}
type InodeMeta struct {
	Name     string
	Attr     map[string]string
	BlkSize  uint64
	NodeId   string
	StartPos uint64
	EndPos   uint64
}
