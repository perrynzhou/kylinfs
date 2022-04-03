package utils

type ChunkServer struct {
	Id          string
	ChunkAddr   string
	ChunkPort   string
	BlockMbSize float64
	TotalMbSize float64
	FreeMbSize  float64
	CurChunkId  uint64
}

type ChunkBlkInfo struct {
	ServerId string
	BlkInfo  map[uint64]*ChunkBlkMeta
	BlkVec   []*ChunkBlkMeta
}
type ChunkBlkMeta struct {
	BlkId      uint64
	BlkSize    float64
	DelSize    float64
	InodeCount uint64
}
type Inode struct {
	Name     string
	Attr     map[string]string
	BlkSize  uint64
	NodeId   string
	StartPos uint64
	EndPos   uint64
	IsActive bool
}
