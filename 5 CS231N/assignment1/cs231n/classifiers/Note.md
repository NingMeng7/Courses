$\nabla_{W_{y_i}} L_i = -x_i^T \sum_{j:y_j \neq y_i}  \mathcal{I} (w_j^T x_i - w_j^Tx_i + 1>0)$

$\nabla_{w_j} L_i = x_i \mathcal{I} (w_j^T x_i - w_j^Tx_i + 1>0)$, $y_j \neq y_i$

$\nabla_{w_j} L = \sum_{i=1}^N \nabla_{w_j} L_i$

$\partial L /\partial w_{mn} = \sum_{i=1}^N x_{im} C_{in}$ 

对N个样本的真实label, $(i, y_i)$. 假设$(i_0, y_i) = y_n$ 那么它会对$w_{i_0, n}$ 贡献 $-\sum_k C_{i_0, k} * x_{i_0, m}$

