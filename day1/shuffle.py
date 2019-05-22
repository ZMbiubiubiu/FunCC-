import random
from collections import namedtuple

Card = namedtuple('Card', 'rank suit')

class Cards:
    ranks = [str(i) for i in range(2,11)] + list('JQKA')
    suits = 'spades diamonds clubs hearts'.split()
    
    def __init__(self):
        self._cards = [Card(rank, suit) for rank in self.ranks
                                        for suit in self.suits]
    
    def __len__(self):
        return len(self._cards)

    def __getitem__(self,index):
        return self._cards[index] 

    def shuffle(self):
        """洗牌"""
        random.shuffle(self._cards) 

    def __repr__(self):
        """显示"""
        for card in self._cards:
            print(card)
        return "显示完毕"

if __name__ == "__main__":
    cards = Cards()
    print(len(cards))
    print(repr(cards))
    # 洗牌
    print(cards.shuffle())
    print(repr(cards))

    