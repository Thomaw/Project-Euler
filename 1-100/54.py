  ### easier to get than parsing a file
  ### just using vim and command :s/ /","/g  and  s:/^/["/
  t=[
  ["8C","TS","KC","9H","4S","7D","2S","5D","3S","AC"],
  ["5C","AD","5D","AC","9C","7C","5H","8D","TD","KS"],
    # snipped
  ["QC","KC","3S","JC","KD","2C","8D","AH","QS","TS"],
  ["AS","KD","3D","JD","8H","7C","8C","5C","QD","6C"]
  ]



  ### return an all-numerical sorted hand,
  ### and an array of ranks
  global values
  values = {'2':2, '3':3, '4':4, '5':5, '6':6, '7':7, '8':8, 
            '9':9, 'T':10, 'J':11, 'Q':12, 'K':13, 'A':14, 
            'C':100, 'D':200, 'H':300, 'S':400}
  def makeHand(t):
    n={}
    hand = []
    for i in t:
      rank  = i[0]
      suite = i[1]
      # couting same cards
      try:
        n[values[rank]] += 1
      except:
        n[values[rank]] = 1

      # assigning a vlue to the card to sort them afterwards
      hand.append(values[rank] + values[suite])

    hand.sort()
    return hand, n




  ### compute a 'winning value' of the hand
  def handValue(t):
    (hand, n) = makeHand(t)

    value = 0

    # a pair is 7000, 2 pairs is 9000, full house is 13000, 
    # all different cards is 5000, ...
    for i in n:
      value += n[i]**2
    value *= 1000

    # consec. values is worth 12000
    if value == 5000:
      if min(n) + 4 == max(n):
        value = 12000

    # same suite is worth 12500 if no consecutives values,  
    # 19500 if they are
    if hand[0] / 100 == hand[-1] / 100:
      value += 7500

    # cryptic thing to add the maximum value of the maximum 
    # represented cards
    value += max([i for i in n if n[i]==max([n[k] for k in n])])
    return value


  win1 = 0
  for i in range(0, len(t)):
    h1 = handValue(t[i][0:5])
    h2 = handValue(t[i][5:])
    if h1 > h2:
      win1 += 1

  print win1
